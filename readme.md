
# Spring 2024 Soldering Workshop

This is a soldering workshop designed for beginners to put together a stylophone, a music-making device that outputs via a buzzer.


# Programming the Board

## Prerequisites

1. Programming the board requires make to be installed and available via bash. Files to download make can be found here:
* Windows: https://gnuwin32.sourceforge.net/packages/make.htm
* Unix: https://www.gnu.org/software/make/
2. Programming is also reliant on a ICSP 6-pin programming board. For for these purposes, we are using an arduino nano and a customized breakout board to act as a programmer. These instructions can be found here: ____________________.
3. The Makefile assumes you are targeting an ATMega328P, the microcontroller this is targeted for.

## Actually programming the board

1. Download the directory labeled "Programming" and navigate to it. 
2. Find the COM port that the programmer is connected to. Replace the COMX on line 2 of the Makefile with the port that the programmer is connected to. 
    `... -c stk500v1 -P COMX -b 19200 -U ...`
3. Using terminal in the same folder, type `Make`


