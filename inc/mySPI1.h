/**
 * @file mySPI1.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Handles the SPI1 connection, used for Sending data 
 *        via the lcd_driver to the LCD_Display.
 */

#ifndef __MYSPI1_H
#define __MYSPI1_H

#include "main.h"

/**
 * @brief Initialises the pins for spi1
 * 
 * @param spiHandler pointer to the spi1 perihperal 
 * 
 * @return void function
 */
void initSPI1(SPI_TypeDef *spiHandler);

/**
 * @brief Initialises the spi1 and sets specific configurations
 * 
 * @see set clock polarity to 0
 * @see spi1 in mastermode
 * @see set Baud rate to 2MHz
 * @see receive only mode
 * @see set software slave management 
 * @see set internal slave select
 * @see set 8-bit data format
 * @see disable ss output
 * @see set spi motorola mode
 * 
 * @return void function 
 */
void initMySPI1();

#endif 
