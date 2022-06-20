# README.md

## Introduction
In the course of developing for the TM4C123G board (Cortex M4 Processor), I found myself rewriting a good amount of code
to interface with a 16x2 LCD screen. As such, I've developed a simple driver to interface between the board and display.
Specifically, this driver was developed using the [LCM-S01602DSF/A](https://www.lumex.com/datasheet/LCM-S01602DSF+A.html) LCD.
However, as many 16x2 LCD screens operate with the same wire connections, this library can be adapted and treated more generally.

## Features
- simple library to perform writes to a 16x2 LCD screen from a TM4c123G evaluation board
- breaks down 11 command bits into 3 nibbles for easier development on device with limited number of pins
- contains basic functions for configuring LCD, updating DDRAM, writing single character, and writing rows.

### To Do
- implement make file for easier building, board independent building
- implement 4 bit mode write commands
- implement read commands
- remove need for clock dependent wait function
- remove SysTick specific wait implementation

## Build
**TBD**

## Configuration
To adapt the library to your board, you will primarily work with the the function '''LCD_16x2_Init()''' to designate which 
PORTS you are using. In the future, you will need to designate  at least 2 busses/ports of 4 bits each. As of now, you will
need to designate 3 series of 4 wires:

1. Upper 4 data bits.
2. Lower 4 data bits.
3. 3 control bits.

In the current configuration, Port D Pins 0-3 are used for the lower data bits, Port A Pins 2-5 are used for the upper data bits, 
and Port F Pins 0-2 are used for the control bits.  

