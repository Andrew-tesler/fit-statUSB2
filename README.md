Short description

USB connected diplay with Leds and 2 buttons. Will show messages sent by the user and display LEDs RGB

Based on TI MSP430

HW

MSP430F5528 - Has variants of packages allowing the device to be shrinked. 128 x 64 LCD, SSD1306 driver 4 Leds (Square footprint) 2 buttons

The follwoing should be implimented or addresed

i2c LCD Code
Adding 2 buttons That the LCD will push on them (Need to test this)
USB code
USB keyboard as feedback fro button presses?

Project setup

Install Code Composer 8 and later
Install MSP430Ware Driver Libraries
Import Empty_Project_MSP430F5xx_6xx_Grlib_Example Project in the Graphics Driver library. 
Rename to fit-statUSB2 
Setup Project Configuration to your board(MSP430F5529/28)

Copy git project files to the directory overwriting the existing files.