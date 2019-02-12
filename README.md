Project Under development collection of concept and proof of concept for fit-statUSB2 project

[![GitHub version](https://img.shields.io/github/release/blynkkk/blynk-server.svg)](https://github.com/Andrew-tesler/fit-statUSB2/releases/latest)
[![GitHub download](https://img.shields.io/github/downloads/blynkkk/blynk-server/total.svg)](https://github.com/blynkkk/blynk-server/releases/latest)
[ ![Build Status](https://travis-ci.org/blynkkk/blynk-server.svg?branch=master)](https://travis-ci.org/blynkkk/blynk-server)



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

Install Code Composer 8 and later<br>
Install MSP430Ware Driver Libraries<br>
Import Empty_Project_MSP430F5xx_6xx_Grlib_Example Project in the Graphics Driver library.<br> 
Rename to fit-statUSB2<br>
Setup Project Configuration to your board(MSP430F5529/28)<br>
Copy git project files to the directory overwriting the existing files.<br>

Import C1_LedOnOff Project 

-- Add to project Properaties/ Include options / ${PROJECT_ROOT}/USB_config
-- Copy to project librarys of USB...
