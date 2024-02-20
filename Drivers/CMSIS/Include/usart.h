/**************************************************************************//**
 * @file     initialiser.h
 * @brief    initialiser header file
 * @version  V1.0
 * @date     13. December 2023
 ******************************************************************************/
/*
 * Copyright Silvan Spiess, Sarah Allemann
 */

#ifndef __USART_H
#define __USART_H

#include "main.h"
#include "pacer.h"

/**
 * @brief  TODO.
 * @return Returns the message sent to USART
 */
void createStringForUSART(uint16_t channel, uint16_t temperature);

/**
 * @brief  TODO.
 * @return void function
 */
void sendStringUSART(unsigned char *strng);

/**
 * @brief  TODO.
 * @return void function
 */
void initUSART();

/**
 * @brief  TODO.
 * @return void function
 */
void usart_write(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t msgLength);

/**
 * @brief  TODO.
 * @return void function
 */
void usart_readByte(USART_TypeDef *USARTx, uint8_t *buffer);

/**
 * @brief  TODO.
 * @return void function
 */
void usart_periperal_init(USART_TypeDef *USARTx);

#endif 
