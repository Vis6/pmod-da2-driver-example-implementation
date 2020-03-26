/*
 * da2_driver.h
 *
 * Created on: Mar 9, 2020
 * Author: Ximu Zhang
 *
 * This program is used to drive the Digilent PMOD DA2 using PMOD JE1-4 on the
 * Zynq 7000 Zedboard.
 */

#ifndef SRC_DA2_DRIVER_DA2_DRIVER_H_
#define SRC_DA2_DRIVER_DA2_DRIVER_H_

/***************************** Include Files *********************************/
#include "xgpiops.h"

/************************** Constant Definitions *****************************/
/*
 * Signal definitions
 *
 * PMOD DA2 has six input pins:
 *     Pin 1: ~SYNC - connect to JE1
 *     Pin 2: DINA	- connect to JE2
 *     Pin 3: DINB	- connect to JE3
 *     Pin 4: SCLK	- connect to JE4
 *     Pin 5: GND	- connect to JE5
 *     Pin 6: VCC	- connect to JE6
 *
 * Signal Name Zynq pin MIO
 * ----------- -------- --------
 * JE1			A6		MIO13
 * JE2			G7		MIO10
 * JE3			B4		MIO11
 * JE4			C5		MIO12
 * JE7			G6		MIO0
 * JE8			C4		MIO9
 * JE9			B6		MIO14
 * JE10			E6		MIO15
 */
#define JE1		13
#define JE2		10
#define JE3		11
#define JE4		12
#define JE7		 0
#define JE8		 9
#define JE9		14
#define JE10	15

#define SYNC_PIN	 JE1
#define CHANNEL1_PIN JE2
#define CHANNEL2_PIN JE3
#define SCLK_PIN	 JE4
#define HIGH_SIGNAL	 1
#define LOW_SIGNAL	 0

/*
 * Timing information
 * Unit: ns
 * The numbers are the minimum delay time
 * Not used in the example based on Zedboard
 */
#define T_SYNC 25
#define T_SCLK 25
#define T_U    20
#define T_L    20
#define T_CS    1

/************************** Function Prototypes ******************************/
/*
 * Function to init the gpio ports (PS side) used by PMOD DA2.
 */
void da2Init(XGpioPs *InstancePtr, XGpioPs_Config *Config, u16 DeviceId);

/*
 * Function to transmit data.
 */
void transmitData(u16 buffer[2], XGpioPs *InstancePtr);

/*
 * Function for delay.
 */
void transmitDelay(int delay);

#endif /* SRC_DA2_DRIVER_DA2_DRIVER_H_ */
