/**
 * @file usart.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Comunication with an external connected application (H-Term) using USART via spi2.
 */

#ifndef __USART_H
#define __USART_H

#include "main.h"

/**
 * @brief  Puts together a string using snprintf.
 * @return void function
 */
void createStringForUSART(uint16_t channel, uint16_t temperature);

/**
 * @brief  Sends the given String .
 * @return void function
 */
void sendStringUSART(unsigned char *strng);

/**
 * @brief  Initialises the USART gpio pins.
 * 
 * @see PA2 -> open drain
 * @see PA3 -> open drain
 * 
 * @return void function
 */
void initUSART();

/**
 * @brief  Initialises the USART register
 * 
 * @see set data fromat to 8 bits
 * @see select a stop bit
 * @see disable parity control
 * @see set oversmapling to 16 bits
 * @see set Baud rate to 115200Hz
 * @see Enable transmission and reception
 * 
 * @param
 * 
 * @return void function
 */
void usart_periperal_init(USART_TypeDef *USARTx);

/**
 * @brief  write bit by bit to data register.
 * @return void function
 */
void usart_write(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t msgLength);

/**
 * @brief  Read bit by bit from data register.
 * @return void function
 */
void usart_readByte(USART_TypeDef *USARTx, uint8_t *buffer);

#endif 
