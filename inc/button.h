/**
 * @file button.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Handles the button (joystick) inputs.
 */

#ifndef __BUTTON_H
#define __BUTTON_H

#include "main.h"

extern uint16_t switchFreq;
extern bool channel_1;
extern bool channel_2;
extern bool prev_left;
extern bool prev_right;

/**
 * @brief  This handler, when triggered, decreases the frequency of the timer,
 *         to measure the temperature to the next lower frequency.
 * 
 * @see triggers when pressing SW_DOWN (PB0)
 * 
 * @return void function
 */
void EXTI0_IRQHandler();

/**
 * @brief This handler (TIM2 timer) checks, wether SW_LEFT (PC1) or SW_RIGHT (PC0) 
 *        have been pressed and activates/deactivates the corresponding channels:
 *        SW_LEFT toggles channel 1
 *        SW_RIGHT toggles channel 2
 * 
 * @see triggers when pressing SW_DOWN (PB0)
 * 
 * @return void function
 */
void EXTI2_IRQHandler();

/**
 * @brief  This handler, when triggered, increases the frequency of the timer,
 *         to measure the temperature to the next higher frequency.
 * 
 * @see triggers when pressing SW_UP (PA4)
 * 
 * @return void function
 */
void EXTI4_IRQHandler();

/**
 * @brief  This handler, when triggered, checks how long the push of the button is 
 *         and does the following actions:
 *         short hold: toggle the measureing on and off* 
 *         long hold: reset the frequency of measuring to the base frequency (1Hz)
 * 
 * @see triggers when pressing SW_CENTER (PB5)
 * 
 * @return void function
 */
void EXTI9_5_IRQHandler();

/**
 * @brief  This function initialises the pins for all buttons. 
 * 
 * @return void function
 */
void initRegularButtons();

/**
 * @brief  This function initialises the interrupts needed for the buttons. 
 * 
 * @return void function
 */
void initButtonInterrupts();

#endif 
