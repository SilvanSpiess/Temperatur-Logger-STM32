/**
 * @file lcd.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Initialises LCD_Display as well as maintains its handles it 
 * during runtime of the program.
 */

#ifndef __LCD_H
#define __LCD_H

#include "main.h"
#include "lcd_menu.h"

/**
 * @brief Prints the inital screen on the LCD_Display
 * 
 */
void screenSetup();

/**
 * @brief Initialises all pins required for the LCD_Display
 * @return void function
 */
void initialScreen();

/**
 * @brief Updates the screen based on inputs from the 
 * TIM6_DAC_IRQHandler function in pacer.c
 * 
 * @param te_1 Measured Temperature of channel 1
 * @param te_2 Measured Temperature of channel 2
 * @param ch_1 Boolean that indicates if Channel 1 is on (1) or off (0)
 * @param ch_2 Boolean that indicates if Channel 2 is on (1) or off (0)
 * @param isOn Boolean that keeps track of the flashing temperatures on the LCD_Display
 * 
 * @return void function
 */
void updateScreen(uint16_t te_1, uint16_t te_2, uint16_t ch_1, uint16_t ch_2, uint16_t isOn);
#endif 
