/**************************************************************************//**
 * @file     button.h
 * @brief    button handling header file
 * @version  V1.0
 * @date     13. December 2023
 ******************************************************************************/
/*
 * Copyright Silvan Spiess, Sarah Allemann
 */

#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

extern uint16_t switchFreq;
extern uint16_t channel_1;
extern uint16_t channel_2;

void checkbutton();

/**
 * @brief  This Handler, when triggered, decreases the Frequency of the Timer,
 *         to measure the temperature to the next lower Frequency.
 * @return void function
 */
void EXTI0_IRQHandler();

/**
 * @brief  This Handler, when triggered, increases the Frequency of the Timer,
 *         to measure the temperature to the next higher Frequency.
 * @return void function
 */
void EXTI4_IRQHandler();

/**
 * @brief  TODO.
 * @return void function
 */
void EXTI9_5_IRQHandler();

/**
 * @brief  TODO.
 * @return void function
 */
void initRegularButtons();

/**
 * @brief  This function initialises the Interrupts needed for the buttons.
 * @return void function
 */
void initButtonInterrupts();

#endif 
