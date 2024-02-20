# Project description

This project is a temperature logger based on the mbed application shield scheme. 
It uses the joystick for control and the RGB LED for user feedback. 
The joystick enables the activation/deactivation of channels,
adjusting the sampling frequency and starting/stopping measurements. 
The RGB LED indicates the current status of the channels and the sampling frequency.

### Authorship

The project was developed by Spiess Silvan and Allemann Sarah.

### Dependencies

To use the project, the following requirements must be met:

- The mbed application shield schema must be connected.
- A functional joystick is required.
- The RGB LED must be connected correctly.
- A temperature sensor must be connected to a microcontroller channel.
- The STM32F4xx_HAL_Driver library.

### Instructions for use

THe following conditions/requirements in the H-Term application must be met, in order to have a functional temperature logger.\

- The port is set to ACM 0 or 1
- The baud rate is set to 115200 
- A New Line to LF is used *(optional)*
- The temperature logger is plugged in via a USB-cable

For Debugging purposes, the Project can be cloned from the [Grp-11 Gitlab Repository](https://gitlab.ti.bfh.ch/btf3232/students_hs23/project/grp-11) \
In order to use the debugger, make sure to have Cortex installed in vs-code as well as other necessairy applications found here: [Temperature Logger](https://mikrocontroller.ti.bfh.ch/tutorials/ex-00.html)

### Control and user interface

The user interface is based on the mbed application shield with the following hardware components \
- Joystick
- RGB_LED
- LCD_Display

#### Joystick control functions

- **LEFT:** Toggle channel I (left).
- **RIGHT:** Toggle channel II (right).
- **UP:** Double sampling frequency.
- **DOWN:** Halve the sampling frequency.
- **CENTER:**
  - Short press: Start/stop measurement process.
  - Long press (more than 3 seconds): Set current sampling frequency to standard frequency (1Hz).

##### SAMPLING FREQUENCY

The sampling frequency is the period of time in which the activated channels are read and the data is sent to the computer via the UART. 
The default frequency of 1 Hz is used at the start.

- Possible frequencies are 0.5, 1, 2 and 4 Hz

#### RGB_LED

The LED colors indicate the current status of the channels.

In addition, the LED flashes at the same frequency as the current sampling rate.

- **Channel I:** *Green*
- **Channel II:** *Blue*
- **Both:** *Cyan*
- **None:** *Red*
- **Center button pressed:** *Yellow* 

#### LCD_Display

Ontop of the mbed shield is a 128x32 pixel lcd_display mounted. It shows which channel is on/off during the process of measuring. \
If the channel is on, it shows the following output, depednant on the measured temperature of the channel:\
- temperature < 1000°C: temperature (*as whole number*)
- temperature >= 1000°C: **ERR** (*no sensor connected*)

**Good luck using the temperature logger!**
