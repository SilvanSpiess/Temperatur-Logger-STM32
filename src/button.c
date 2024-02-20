/**
 * @file button.c
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

#include "button.h"
#include "led.h"
#include <stdbool.h>

uint16_t switchFreq = 3999;
bool channel_1 = 0;
bool channel_2 = 0;
bool prev_left = 0;
bool prev_right = 0;

void initRegularButtons() {
  // Configure the GPIO for the SW Switch 
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE4_Msk, 0b00 << GPIO_MODER_MODE4_Pos); //SW_UP     PA4
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0_Msk, 0b00 << GPIO_MODER_MODE0_Pos); //SW_DOWN   PB0
  MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE1_Msk, 0b00 << GPIO_MODER_MODE1_Pos); //SW_LEFT   PC1
  MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE0_Msk, 0b00 << GPIO_MODER_MODE0_Pos); //SW_RIGHT  PC0
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE5_Msk, 0b00 << GPIO_MODER_MODE5_Pos); //SW_CENTER PB5
}

void initButtonInterrupts() {
  // SW_UP PA4  
  SET_BIT(EXTI->IMR, EXTI_IMR_MR4);         // Set Interrupt Mask Register  
  SET_BIT(EXTI->RTSR, EXTI_RTSR_TR4);       // Set Rising Trigger Selection Register  
  SET_BIT(SYSCFG->EXTICR[0], SYSCFG_EXTICR2_EXTI4_PA);// Set SYSCFG_EXTICR2   
  SET_BIT(EXTI->PR, EXTI_PR_PR4);           // Set (Clear) PR (Pending Register)

  NVIC_SetPriority(EXTI4_IRQn, 1);          // Set NVIC_IPRx (Interrupt Priority Register)   
  NVIC_ClearPendingIRQ(EXTI4_IRQn);         // Set NVIC_ICPRx (Interrupt Clear-Pending Register)  
  NVIC_EnableIRQ(EXTI4_IRQn);               // Set NVIC_ISERx (Interrupt Set-Enable Register)
  
  // SW_DOWN PB0
  SET_BIT(EXTI->IMR, EXTI_IMR_MR0);
  SET_BIT(EXTI->RTSR, EXTI_RTSR_TR0);
  SET_BIT(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI0_PB);
  SET_BIT(EXTI->PR, EXTI_PR_PR0);
  
  NVIC_SetPriority(EXTI0_IRQn, 1);
  NVIC_ClearPendingIRQ(EXTI0_IRQn);
  NVIC_EnableIRQ(EXTI0_IRQn);
  
  // SW_CENTER PB5
  SET_BIT(EXTI->IMR, EXTI_IMR_MR5);
  SET_BIT(EXTI->RTSR, EXTI_RTSR_TR5);
  SET_BIT(SYSCFG->EXTICR[1], SYSCFG_EXTICR2_EXTI5_PB);
  SET_BIT(EXTI->PR, EXTI_PR_PR5);

  NVIC_SetPriority(EXTI9_5_IRQn, 1);
  NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
  NVIC_EnableIRQ(EXTI9_5_IRQn);

  SET_BIT(TIM2->DIER, TIM_DIER_UIE);

  WRITE_REG(TIM2->PSC, 45000);            // 45MHz -> 1000Hz
  WRITE_REG(TIM2->ARR, 1000000);          // count 1/1000s

  NVIC_SetPriority(TIM2_IRQn, 1);
  NVIC_ClearPendingIRQ(TIM2_IRQn);
  NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void) {
  CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
  if(READ_BIT(GPIOC->IDR, GPIO_IDR_ID1)) { //SW_LEFT PC1
    if(!prev_left) {
      if(channel_1) 
        channel_1 = false;
      else 
        channel_1 = true; 
      prev_left = true;    
    }  
  }
  else if(READ_BIT(GPIOC->IDR, GPIO_IDR_ID0)) { //SW_RIGHT PC0
    if(!prev_right) {
      if(channel_2) 
        channel_2 = false;
      else 
        channel_2 = true; 
      prev_right = true;      
    }                  
  }
  else {
    prev_left = false; 
    prev_right = false;
  } 
  SET_BIT(TIM2->EGR, TIM_EGR_UG); // Generate an update event to load the new ARR value  
}

void EXTI0_IRQHandler() { //SW_DOWN PB0   
  SET_BIT(EXTI->PR, EXTI_PR_PR0);
  //Value for 0.5Hz: 5655
  //Value for 1 Hz:  3999 
  //Value for 2 Hz:  2827 
  //Value for 4 Hz:  1999 
  if(switchFreq == 1999) 
    switchFreq = 2827; 
  else if(switchFreq == 2827) 
    switchFreq = 3999;  
  else switchFreq = 5655;  
  WRITE_REG(TIM6->PSC, switchFreq);
  WRITE_REG(TIM6->ARR, switchFreq);  
}

void EXTI4_IRQHandler() { // SW_UP PA4
  //Value for 0.5Hz: 5655
  //Value for 1 Hz:  3999
  //Value for 2 Hz:  2827
  //Value for 4 Hz:  1999
  SET_BIT(EXTI->PR, EXTI_PR_PR4);
  if(switchFreq == 5655) 
    switchFreq = 3999;
  else if(switchFreq == 3999)
    switchFreq = 2827;
  else switchFreq = 1999;
  WRITE_REG(TIM6->PSC, switchFreq);
  WRITE_REG(TIM6->ARR, switchFreq);  
}

void EXTI9_5_IRQHandler() { // SW_CENTER PB5
  if(READ_BIT(EXTI->PR, EXTI_PR_PR5)) { 
    SET_BIT(EXTI->PR, EXTI_PR_PR5);
    NVIC_DisableIRQ(EXTI9_5_IRQn);
    LED_BLUE_OFF;
    LED_RED_ON;
    LED_GREEN_ON; 
    for(uint32_t x = 4800000; x; x--) {
      if(!READ_BIT(GPIOB->IDR, GPIO_ODR_OD5)) { // Short Press
        if(READ_BIT(TIM6->CR1, TIM_CR1_CEN)) {  // Timer is on            
          CLEAR_BIT(TIM6->CR1, TIM_CR1_CEN);    // Turn Timer off
          // Turn all lamps off
          LED_BLUE_OFF;
          LED_RED_OFF;
          LED_GREEN_OFF;
        }
        else SET_BIT(TIM6->CR1, TIM_CR1_CEN); // else Turn Timer on
        NVIC_EnableIRQ(EXTI9_5_IRQn);
        return;      
      }
    }
    switchFreq = 3999;
    WRITE_REG(TIM6->PSC, switchFreq);
    WRITE_REG(TIM6->ARR, switchFreq);
    NVIC_EnableIRQ(EXTI9_5_IRQn);  
  }
}
