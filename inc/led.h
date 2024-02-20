/**
 * @file led.h
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Controls the LED, inlcuding initialisation.
 */

#ifndef __LED_H
#define __LED_H

#include "main.h"

#define LED_BLUE_ON CLEAR_BIT(GPIOA->ODR, GPIO_ODR_OD9)
#define LED_RED_ON CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD4)
#define LED_GREEN_ON CLEAR_BIT(GPIOC->ODR, GPIO_ODR_OD7)

#define LED_BLUE_OFF SET_BIT(GPIOA->ODR, GPIO_ODR_OD9)
#define LED_RED_OFF SET_BIT(GPIOB->ODR, GPIO_ODR_OD4)
#define LED_GREEN_OFF SET_BIT(GPIOC->ODR, GPIO_ODR_OD7)

#define IS_LED_BLUE (!READ_BIT(GPIOA->ODR, GPIO_ODR_OD9))
#define IS_LED_RED (!READ_BIT(GPIOB->ODR, GPIO_ODR_OD4))
#define IS_LED_GREEN (!READ_BIT(GPIOC->ODR, GPIO_ODR_OD7))

/**
 * @brief Initialises the LED output pins
 * @return void function
 */
void initLeds();

/**
 * @brief This function controls the LED and based in its inputs, sets the state of the LED
 * 
 * @param t_1 Measured Temperature of channel 1
 * @param t_2 Measured Temperature of channel 2
 * @param ch_1 Boolean that indicates if Channel 1 is on (1) or off (0)
 * @param ch_2 Boolean that indicates if Channel 2 is on (1) or off (0)
 * @param isMeasuringLed Boolean that keeps track of the flashing LED
 * 
 * @return void function
 */
void setLED(uint16_t t_1, uint16_t t_2, uint16_t ch_1, uint16_t ch_2, uint16_t isMeasuringLed);

#endif 
