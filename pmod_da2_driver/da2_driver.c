/*
 * da2_driver.c
 *
 * Created on: Mar 9, 2020
 * Author: Ximu Zhang
 *
 * This program is used to drive the Digilent PMOD DA2 using PMOD JE1-4 on the
 * Zynq 7000 Zedboard.
 */

/***************************** Include Files *********************************/
#include "da2_driver.h"
#include "xgpiops.h"
#include "xil_printf.h"

/************************** Function Prototypes ******************************/
/*
 * Initialize the gpio port for PMOD DA2. In this case, JE1-4 are initialized.
 *
 * @param	InstancePtr is a pointer to the XGpioPs instance.
 * @param	ConfigPtr is a reference to a structure containing information
 *		 about a specific QSPI device. This function initializes an
 *		 InstancePtr object for a specific device specified by the
 *		 contents of Config.
 * @param	DeviceId contains the ID of the device to look up the
 *		 configuration for.
 *
 * @return	None.
 */
void da2Init(XGpioPs *InstancePtr, XGpioPs_Config *Config, u16 DeviceId)
{
	// local variables
	int Status;

	// ps gpio configuration
	Config = XGpioPs_LookupConfig(DeviceId);
	Status = XGpioPs_CfgInitialize(InstancePtr, Config, Config->BaseAddr);
	if (Status != XST_SUCCESS)
	{
		xil_printf("PS MIO GPIO Initialize failed!\n");
	}
	else
	{
		xil_printf("PS MIO GPIO Initialize succeed!\n");
	}

	// set gpio derection and enable output
	XGpioPs_SetDirectionPin(InstancePtr, SYNC_PIN, 1); // JE1, output
	XGpioPs_SetOutputEnablePin(InstancePtr, SYNC_PIN, 1);
	XGpioPs_WritePin(InstancePtr, SYNC_PIN, LOW_SIGNAL);

	XGpioPs_SetDirectionPin(InstancePtr, CHANNEL1_PIN, 1); // JE2, output
	XGpioPs_SetOutputEnablePin(InstancePtr, CHANNEL1_PIN, 1);
	XGpioPs_WritePin(InstancePtr, CHANNEL1_PIN, LOW_SIGNAL);

	XGpioPs_SetDirectionPin(InstancePtr, CHANNEL2_PIN, 1); // JE3, output
	XGpioPs_SetOutputEnablePin(InstancePtr, CHANNEL2_PIN, 1);
	XGpioPs_WritePin(InstancePtr, CHANNEL2_PIN, LOW_SIGNAL);

	XGpioPs_SetDirectionPin(InstancePtr, SCLK_PIN, 1); // JE4, output
	XGpioPs_SetOutputEnablePin(InstancePtr, SCLK_PIN, 1);
	XGpioPs_WritePin(InstancePtr, SCLK_PIN, LOW_SIGNAL);
}

/*
 * Send data to the PMOD DA2.
 *
 * @param	Buffer is a one dimensional array containing two unsigned
 * 		 16-bit integers.
 * @param	InstancePtr is a pointer to the XGpioPs instance.
 *
 * @return	None.
 */
void transmitData(u16 buffer[2], XGpioPs *InstancePtr)
{
	u16 mask[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
				  0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000};

	XGpioPs_WritePin(InstancePtr, SYNC_PIN, HIGH_SIGNAL); // set SYNC high
	transmitDelay(2);
	XGpioPs_WritePin(InstancePtr, SYNC_PIN, LOW_SIGNAL); // set SYNC low
	transmitDelay(1);

	for (int i = 15; i >= 0; i--)
	{
		XGpioPs_WritePin(InstancePtr, SCLK_PIN, HIGH_SIGNAL); // set SCLK high
		transmitDelay(1);
		XGpioPs_WritePin(InstancePtr, SCLK_PIN, LOW_SIGNAL); // set SCLK low

		XGpioPs_WritePin(InstancePtr, CHANNEL1_PIN, ((buffer[0] & mask[i])) >> i);// send data to channel 1
		XGpioPs_WritePin(InstancePtr, CHANNEL2_PIN, ((buffer[1] & mask[i])) >> i);// send data to channel 2
		transmitDelay(2);
	}

	XGpioPs_WritePin(InstancePtr, SYNC_PIN, HIGH_SIGNAL); // set SYNC high
}

/*
 * Time delay.
 *
 * @param	delay is the number of loop.
 *
 * @return	None.
 */
void transmitDelay(int delay)
{
	for (int i = 0; i < delay; i++)
	{
		asm("NOP");
	}
}
