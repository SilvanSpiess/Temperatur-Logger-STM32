/**
 * @file mySPI2.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Handles the SPI2 connection, used for Sending data 
 *        via USART to an externally connected application (h-term).
 */

#ifndef __MYSPI2_H
#define __MYSPI2_H

#include "main.h"

/**
 * @brief Initialises the pins for spi2
 *  
 * @param spiHandler pointer to the spi1 perihperal
 *  
 * @return void function
 */
void initSPI2(SPI_TypeDef *spiHandler);

/**
 * @brief Initialises the spi2 and sets specific configurations
 * 
 * @see set clock polarity to 0
 * @see spi2 in mastermode
 * @see set Baud rate to 0.5MHz
 * @see receive only mode
 * @see set software slave management 
 * @see set internal slave select
 * @see set 16-bit data format
 * @see disable ss output
 * @see set spi motorola mode
 * 
 * @return void function
 */
void initMySPI2();

#endif 
