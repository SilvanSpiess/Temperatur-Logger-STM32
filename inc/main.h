/**
 * @file main.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Program entry point. Calls all initialisers, then runs the main loop. Initialises all clocks.
 */

#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include "stm32f4xx.h"
#include "stm32f446xx.h"

#include "button.h"
#include "pacer.h"
#include "led.h"
#include "usart.h"
#include "mySPI1.h"
#include "mySPI2.h"
#include "lcd.h"

#define LCD_SCK_Pin GPIO_PIN_5
#define LCD_SCK_GPIO_Port GPIOA
#define LCD_RESET_Pin GPIO_PIN_6
#define LCD_RESET_GPIO_Port GPIOA
#define LCD_MOSI_Pin GPIO_PIN_7
#define LCD_MOSI_GPIO_Port GPIOA
#define LCD_A0_Pin GPIO_PIN_8
#define LCD_A0_GPIO_Port GPIOA
#define LCD_CS_N_Pin GPIO_PIN_6
#define LCD_CS_N_GPIO_Port GPIOB

/**
 * @brief Initialises all clocks, if module isn't "acting/reacting", check here!
 * 
 * @return void function
 */
void initClocks();

#endif
