/**
 * @file pacer.c
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Selective frequency handling header file. It initiates 
 * core processes like measuring temperature and communicating to
 * USART, the lcd.c and the led.c files.
 */
#include "pacer.h"

uint16_t data_1 = 0;
uint16_t data_2 = 0;
uint16_t Temperature_1 = 0;
uint16_t Temperature_2 = 0;
unsigned char msg[25] = "0";
bool isMeasuring = false;

void initPacerInterrupt() {
  // Set MCO1 to check HSI clock source, set prescaler to 4
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO1_Msk, 0b00 << RCC_CFGR_MCO1_Pos);
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO1PRE_Msk, 0b110 << RCC_CFGR_MCO1PRE_Pos);

  SET_BIT(TIM6->CR1, TIM_CR1_URS);            // only CNT overflow/underflow generates update interrupt
  SET_BIT(TIM6->CR1, TIM_CR1_ARPE);           // ARR is buffered
  SET_BIT(TIM6->DIER, TIM_DIER_UIE);          // Update interrupt enable
  CLEAR_BIT(TIM6->SR, TIM_SR_UIF);            // Clear pending interrupt

  NVIC_SetPriority(TIM6_DAC_IRQn, 1);
  NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
  NVIC_EnableIRQ(TIM6_DAC_IRQn); 
  
  WRITE_REG(TIM6->PSC, switchFreq);
  WRITE_REG(TIM6->ARR, switchFreq); 
}

void TIM6_DAC_IRQHandler(void) {
  // Clear update interrupt flag
  if(READ_BIT(TIM6->SR, TIM_SR_UIF) != 0) {
    CLEAR_BIT(TIM6->SR, TIM_SR_UIF);
    if(!isMeasuring) {
      setLED(0, 0, 0, 0, isMeasuring);
      isMeasuring = true;      
      return;
    } 
    else {
      if(channel_1) {    
        // Enable SPI Channel
        CLEAR_BIT(GPIOA->ODR, GPIO_ODR_OD15);
        SET_BIT(SPI2->CR1, SPI_CR1_SPE);
        // Read data_1
        while(!READ_BIT(SPI2->SR, SPI_SR_RXNE)) {;}
        data_1 = READ_REG(SPI2->DR);
        while(!READ_BIT(SPI2->SR, SPI_SR_RXNE)) {;}
        READ_REG(SPI2->DR); //Dummy Reader
        // Disable SPI Channel
        CLEAR_BIT(SPI2->CR1, SPI_CR1_SPE);
        SET_BIT(GPIOA->ODR, GPIO_ODR_OD15);

        // Calculate Temperature 1
        data_1 &= 0xFFFC; 
        Temperature_1 = data_1 >> 4;
      }
      if(channel_2) {
        // Enable SPI Channel
        CLEAR_BIT(GPIOA->ODR, GPIO_ODR_OD11);
        SET_BIT(SPI2->CR1, SPI_CR1_SPE);
        // Read data_2
        while(!READ_BIT(SPI2->SR, SPI_SR_RXNE)) {;}
        data_2 = READ_REG(SPI2->DR); 
        while(!READ_BIT(SPI2->SR, SPI_SR_RXNE)) {;}
        READ_REG(SPI2->DR); //Dummy Reader
        // Disable SPI Channel
        CLEAR_BIT(SPI2->CR1, SPI_CR1_SPE);
        SET_BIT(GPIOA->ODR, GPIO_ODR_OD11);  

        // Calculate Temperature 2
        data_2 &= 0xFFFC; 
        Temperature_2 = data_2 >> 4;     
      }
      if(channel_1) {       
        createStringForUSART(1, Temperature_1);    
        sendStringUSART(msg);      
      } 
      if(channel_2) {      
        createStringForUSART(2, Temperature_2);  
        sendStringUSART(msg);      
      } 
      updateScreen(Temperature_1, Temperature_2, channel_1, channel_2, isMeasuring);
      setLED(Temperature_1, Temperature_2, channel_1, channel_2, isMeasuring);
      isMeasuring = false;
    }     
  }
}