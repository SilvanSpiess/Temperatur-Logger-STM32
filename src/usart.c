/**
 * @file usart.c
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

#include "usart.h"

#include <string.h>

void createStringForUSART(uint16_t channel, uint16_t temperature) {    
  snprintf((char *restrict) msg, 64, "%s%d%s%d%s", "Temp_",channel, " = ", temperature, " deg\n");
}

void sendStringUSART(unsigned char *strng) {     
  while (*strng) {         
    usart_write(USART2, strng++, 1); 
  } 
}

void initUSART() {
  // PA2 USART2
  CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE2_0);
  SET_BIT(GPIOA->MODER, GPIO_MODER_MODE2_1);
  // PA3 USART2
  CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE3_0);
  SET_BIT(GPIOA->MODER, GPIO_MODER_MODE3_1);

  // Alternate function AF7 PA2 and PA3
  MODIFY_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL2_Msk, 0x7 << GPIO_AFRL_AFSEL2_Pos);
  MODIFY_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL3_Msk, 0x7 << GPIO_AFRL_AFSEL3_Pos);
  
  // Set Speed high on PA2 and PA3
  MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED2_Msk, 0x3 << GPIO_OSPEEDR_OSPEED2_Pos);
  MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED3_Msk, 0x3 << GPIO_OSPEEDR_OSPEED3_Pos);

  // PA2 00 := No pull −up/ pull −down 01 := pull −up
  SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD2_0);
  CLEAR_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD2_1);
  
  // PA3 00 := No pull −up/ pull −down
  SET_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD3_0);
  CLEAR_BIT(GPIOA->PUPDR, GPIO_PUPDR_PUPD3_1);
  
  // Output type PA2 open−drain
  SET_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT2);
  
  // Output type PA3 open−drain
  SET_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT3);
  // peripheral i n i t i a l i z a t i o n
  usart_periperal_init(USART2);
}

void usart_periperal_init(USART_TypeDef *USARTx) {
  // Disable USART
  CLEAR_BIT(USARTx->CR1, USART_CR1_UE);
  // Set data length to 8
  CLEAR_BIT(USARTx->CR1, USART_CR1_M);
  // Select 1 stop b i t
  CLEAR_BIT(USARTx->CR2, USART_CR2_STOP_0);
  CLEAR_BIT(USARTx->CR2, USART_CR2_STOP_1);
  // Set parity control to no parity
  CLEAR_BIT(USARTx->CR1, USART_CR1_PCE);
  // Set oversampling to 16
  CLEAR_BIT(USARTx->CR1, USART_CR1_OVER8);
  // Set Baud Rate 115200 on a 16 MHz system
  WRITE_REG(USARTx->BRR, 0x8B) ;
  // Set Baud Rate 115200 on a 8 MHz system
  // WRITE_REG(USARTx−>BRR, 0x45 ) ;
  // Set Baud Rate 9600 on a 16MHz system
  // WRITE_REG(USARTx->BRR, 0x683) ;
  // Set Baud Rate 9600 on a 8MHz system
  // WRITE_REG(USARTx−>BRR, 0x683) ;
  // Enable transmission and reception
  SET_BIT(USARTx->CR1, (USART_CR1_TE | USART_CR1_RE) );
  // Enable USART
  SET_BIT(USARTx->CR1, USART_CR1_UE);
}

void usart_readByte(USART_TypeDef *USARTx, uint8_t *buffer) {
  if(buffer == 0) { return; }

  // wait u n t i l data rekceives in the DR
  while(!(USARTx->SR & USART_SR_RXNE)) { ; }

  // read in one byte
  *buffer = USARTx->DR;
}

void usart_write(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t msgLength) {
  if(buffer == 0) { return; }

  // transmit multiple bytes
  for(uint32_t index = 0; index < msgLength; ++index) {
    // wait f o r t r a n s f e r from DR to tx s h i f t r e g i s t e r
    while(!(USARTx->SR & USART_SR_TXE)) { ; }

    // write out one byte
    USARTx->DR = buffer[index] & 0xFF;
  }

  // wait f o r transmission completion
  while(!(USARTx->SR & USART_SR_TC)) { ; }
}