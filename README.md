# Mengjiao_ME433_2017
Repository for ME 433 Advanced Mechatronics assignments and projects

Course Source: https://github.com/ndm736/ME433_2017/wiki

# HW1

HW1 assignment description [here](https://github.com/ndm736/ME433_2017/wiki/HW1). My homework folder [here](https://github.com/MuMu1018/Mengjiao_ME433_2017/tree/master/HW1).

This is my breadboard PIC32 circuit:
![breadboard PIC32 circuit](https://github.com/MuMu1018/Mengjiao_ME433_2017/blob/master/HW1/FullSizeRender.jpg)

Test demo: a blinking LED (at 1 kHz), that stops when pushing and holding the USER pushbutton, and continues when releasings.


# HW2

HW2 assignment description [here](https://github.com/ndm736/ME433_2017/wiki/HW2). My homework folder [here](https://github.com/MuMu1018/Mengjiao_ME433_2017/tree/master/HW2).

This homework is the first half of [HW3](https://github.com/ndm736/ME433_2017/wiki/HW3). We use [Sparkfun Eagle Github libraries](https://github.com/sparkfun/SparkFun-Eagle-Libraries) to create our own libraries.

# HW3

HW3 assignment description [here](https://github.com/ndm736/ME433_2017/wiki/HW3). My homework folder [here](https://github.com/MuMu1018/Mengjiao_ME433_2017/tree/master/HW3).

We create a PCB of our PIC32 circuit, 5cm x 5cm, with header pins at specific locations. Do all of the error checking, generate the Gerber files. This is my design:
![PCB board](https://github.com/MuMu1018/Mengjiao_ME433_2017/blob/master/HW3/PCB%20board_Mengjiao.png)

# HW4 - SPI DAC

HW4 assignment description [here](https://github.com/ndm736/ME433_2017/wiki/HW4). My homework folder [here](https://github.com/MuMu1018/Mengjiao_ME433_2017/tree/master/HW4).

Here's a schematic showing the connections between our PIC32 and this particular DAC ([the MCP4902](https://github.com/ndm736/ME433_2017/blob/master/mcp4902_spi-dac.pdf)) using SPI communication. The DAC outputs on pins V_OUTA (14) and V_OUTB (10).
![DAC schematic](https://github.com/MuMu1018/Mengjiao_ME433_2017/blob/master/HW4/SPI%20circuit%20schematic.pdf)

The DAC outputs:

10Hz sine wave on VoutA + 5Hz triangle wave on VoutB:
![DAC outputs1](https://github.com/MuMu1018/Mengjiao_ME433_2017/blob/master/HW4/%20SPI_5Hz_TriangleWave.jpg)

10Hz sine wave on VoutA + 10Hz triangle wave on VoutB:
![DAC outputs2](https://github.com/MuMu1018/Mengjiao_ME433_2017/blob/master/HW4/%20SPI_10Hz_TriangleWave.jpg)

# HW5 - I2C pin expander

HW5 assignment description [here](https://github.com/ndm736/ME433_2017/wiki/HW5). My homework folder [here](https://github.com/MuMu1018/Mengjiao_ME433_2017/tree/master/HW5).

Here's a schematic showing the connections between our PIC32 and the MCP23008 I/O expander ([datasheet for MCP23008](https://github.com/ndm736/ME433_2017/blob/master/mcp23008_i2c-expander.pdf)) using I2C communication.

![I2C schematic](https://github.com/MuMu1018/Mengjiao_ME433_2017/blob/master/HW5/ME433_HW5.pdf)




