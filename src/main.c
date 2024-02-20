/**
 * @file main.c
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Program entry point. Calls all initialisers, then runs the main loop. Initialises all clocks.
 * 
 */

#include "main.h"

void Error_Handler(void);

int main(void) {
  initClocks();
  initLeds();
  initRegularButtons();
  initButtonInterrupts();
  initPacerInterrupt();

  // USART
  initUSART();
  initMySPI2();
  initSPI2(SPI2);
  
  // LCD
  initMySPI1();
  initSPI1(SPI1);
  lcd_init();
  screenSetup();
  initialScreen();

  // Start timer
  SET_BIT(TIM6->CR1, TIM_CR1_CEN);
  SET_BIT(TIM2->CR1, TIM_CR1_CEN);
  
  /* Infinite loop*/
  while (1) {
    
  }
} /* end main() */

void initClocks() {
  // Enable GPIO clocks
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN); 

  // Enable SYSCFG Clock (interrupts)
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

  // Enable TIM6 Clock (Timer)
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM6EN);
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);

  //Enable USART Clock
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);

  // Enable SPI2 Clock
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);

  // Enable SPI1 Clock
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);
} 

void Error_Handler(void) {
  __disable_irq();
  while (1) {  }
}
