/**
 * @file led.c
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

#include "led.h"

void initLeds() {  
  /* Configure all GPIO LEDs */
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE9_Msk, 0b01 << GPIO_MODER_MODE9_Pos); //BLUE_LED   PA9
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE4_Msk, 0b01 << GPIO_MODER_MODE4_Pos); //RED_LED    PB4
  MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE7_Msk, 0b01 << GPIO_MODER_MODE7_Pos); //GREEN_LED  PC7
}

void setLED(uint16_t t_1, uint16_t t_2, uint16_t ch_1, uint16_t ch_2, uint16_t isMeasuringLed) {
  if(isMeasuringLed) {
    if(ch_1 && !ch_2) {
      LED_BLUE_OFF; LED_RED_OFF; LED_GREEN_ON;         
      return;
    }
    else if(!ch_1 && ch_2) {
      LED_BLUE_ON; LED_RED_OFF; LED_GREEN_OFF;
      return;
    }
    else if(ch_1 && ch_2) {
      LED_BLUE_ON; LED_RED_OFF; LED_GREEN_ON;
      return;
    }
    else { //error
      LED_BLUE_OFF; LED_RED_ON; LED_GREEN_OFF;
      return;
    }
  }
  else {
    LED_BLUE_OFF; LED_RED_OFF; LED_GREEN_OFF;
  }  
}