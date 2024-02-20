/**************************************************************************//**
 * @file     pacer.h
 * @brief    selective frequency handling header file
 * @version  V1.0
 * @date     13. December 2023
 ******************************************************************************/
/*
 * Copyright Silvan Spiess, Sarah Allemann
 */

#ifndef __PACER_H
#define __PACER_H

#include "main.h"
#include "mySPI2.h"
#include "led.h"
#include "lcd.h"
#include "usart.h"
#include "button.h"

extern unsigned char msg[25];

/**
 * @brief  The application entry point.
 * @return 0 in success, not equal to 0 otherwise
 */
void initPacerInterrupt(void);

/**
 * @brief  TODO.
 * @return void function
 */
void TIM6_DAC_IRQHandler(void);

#endif 
