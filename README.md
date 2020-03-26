# Example of DAC implementation using Pmod DA2
## Description
- Source codes for driving Pmod DA2 are provided under the path ".\src\pmod_da2_driver".  
- The example uses Pmod DA2 at PS side of the FPGA board to generate two sinusoidal waves.
## Platform
### Hardware
- The example is based on ZedBoard Zynq-7000 ARM/FPGA SoC Development Board. More information is available here: [ZedBoard Zynq-7000](https://www.xilinx.com/products/boards-and-kits/1-elhabt.html.html).  
- The resource of Digilent Pmod DA2 is here: [Pmod DA2](https://reference.digilentinc.com/reference/pmod/pmodda2/start?_ga=2.65140266.565546699.1585146004-1359382362.1583559704).  
### Software
- Vivado 2018.2  
- Xilinx SDK 2018.2  
## Execution
- Connect the Pmod DA2 to the Pmod JE1 of the FPGA board.
- Place the folder "pmod_da2_driver" and the file "main.c" in the folder "src" of your project.
- Run the code and it should work.
## Result
Two channel sine waves.  
<img src="https://github.com/Vis6/pmod-da2-driver-example-implementation/blob/master/result.jpg" alt="Two channel sine waves" width="354.4" height="265.6" align="left" />
