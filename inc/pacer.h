/**
 * @file pacer.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Selective frequency handling header file. It initiates 
 * core processes like measuring temperature and communicating to
 * USART, the lcd.c and the led.c files.
 */

#ifndef __PACER_H
#define __PACER_H

#include "main.h"

extern unsigned char msg[25];
extern bool isMeasuring;

/**
 * @brief Initialises Interrupt for the pacer (Frequency setting module)
 * @return void function
 */
void initPacerInterrupt(void);

/**
 * @brief TIM6 DAC Interrupt Handler 
 * 
 * This function is considered as core of the program. It handles the interrupt for 
 * TIM6 DAC. It is called when the update interrupt flag (UIF) is set. This function 
 * measures temperature via SPI2 then communicates it via USART to a hterm instance 
 * (if connected) then communicates important data to update the LCD_Display with 
 * the measured temperatues and finally communicates data to update the LED.
 * 
 * @return void function
 */
void TIM6_DAC_IRQHandler(void);

#endif 
