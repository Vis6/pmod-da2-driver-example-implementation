/*
 * main.c: a simple application of PMOD DA2
 * 
 * Created on: Mar 9, 2020
 * Author: Ximu Zhang
 * 
 * This source code implements DAC using PMOD DA2 based on ZedBoard Zynq-7000
 * ARM/FPGA SoC Development Board at PS side to generate sine waves.
 */

// Include files
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "da2_driver.h"

// Sine wave table definition
static unsigned char const sinetable[256] = {
		 0x80, 0x83, 0x86, 0x89, 0x8C, 0x90, 0x93, 0x96,
		 0x99, 0x9C, 0x9F, 0xA2, 0xA5, 0xA8, 0xAB, 0xAE,
		 0xB1, 0xB3, 0xB6, 0xB9, 0xBC, 0xBF, 0xC1, 0xC4,
		 0xC7, 0xC9, 0xCC, 0xCE, 0xD1, 0xD3, 0xD5, 0xD8,
		 0xDA, 0xDC, 0xDE, 0xE0, 0xE2, 0xE4, 0xE6, 0xE8,
		 0xEA, 0xEB, 0xED, 0xEF, 0xF0, 0xF1, 0xF3, 0xF4,
		 0xF5, 0xF6, 0xF8, 0xF9, 0xFA, 0xFA, 0xFB, 0xFC,
		 0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF,
		 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFD,
		 0xFD, 0xFC, 0xFB, 0xFA, 0xFA, 0xF9, 0xF8, 0xF6,
		 0xF5, 0xF4, 0xF3, 0xF1, 0xF0, 0xEF, 0xED, 0xEB,
		 0xEA, 0xE8, 0xE6, 0xE4, 0xE2, 0xE0, 0xDE, 0xDC,
		 0xDA, 0xD8, 0xD5, 0xD3, 0xD1, 0xCE, 0xCC, 0xC9,
		 0xC7, 0xC4, 0xC1, 0xBF, 0xBC, 0xB9, 0xB6, 0xB3,
		 0xB1, 0xAE, 0xAB, 0xA8, 0xA5, 0xA2, 0x9F, 0x9C,
		 0x99, 0x96, 0x93, 0x90, 0x8C, 0x89, 0x86, 0x83,
		 0x80, 0x7D, 0x7A, 0x77, 0x74, 0x70, 0x6D, 0x6A,
		 0x67, 0x64, 0x61, 0x5E, 0x5B, 0x58, 0x55, 0x52,
		 0x4F, 0x4D, 0x4A, 0x47, 0x44, 0x41, 0x3F, 0x3C,
		 0x39, 0x37, 0x34, 0x32, 0x2F, 0x2D, 0x2B, 0x28,
		 0x26, 0x24, 0x22, 0x20, 0x1E, 0x1C, 0x1A, 0x18,
		 0x16, 0x15, 0x13, 0x11, 0x10, 0x0F, 0x0D, 0x0C,
		 0x0B, 0x0A, 0x08, 0x07, 0x06, 0x06, 0x05, 0x04,
		 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
		 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
		 0x03, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x0A,
		 0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x13, 0x15,
		 0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24,
		 0x26, 0x28, 0x2B, 0x2D, 0x2F, 0x32, 0x34, 0x37,
		 0x39, 0x3C, 0x3F, 0x41, 0x44, 0x47, 0x4A, 0x4D,
		 0x4F, 0x52, 0x55, 0x58, 0x5B, 0x5E, 0x61, 0x64,
		 0x67, 0x6A, 0x6D, 0x70, 0x74, 0x77, 0x7A, 0x7D
		 };

// GPIO at PS side
XGpioPs_Config *DA2_GPIO_Config;
XGpioPs DA2_Gpio;

int main()
{
    init_platform();

    // variable definition
    u16 buffer[2]; // data buffer for two-channel PMOD DA2

	// Initialize GPIO port at PS side
	// Only use JE1 - JE4
	da2Init(&DA2_Gpio, DA2_GPIO_Config, XPAR_PS7_GPIO_0_DEVICE_ID);

	while (1)
	{
		for (int i = 0; i < 256; i++) // send data from the sine wave table
		{
			buffer[0] = sinetable[i]; // data for channel 1
			buffer[1] = sinetable[255-i]; // data for channel 2
			transmitData(buffer, &DA2_Gpio); // send data to PMOD DA2
		}
	}

    cleanup_platform();
    return 0;
}
