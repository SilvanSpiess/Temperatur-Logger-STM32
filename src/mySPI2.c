/**
 * @file mySPI2.c
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Handles the SPI2 connection, used for Sending data 
 *        via USART to an externally connected application (h-term).
 */

#include "mySPI2.h"

void initMySPI2() {
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE9_Msk, 0b01 << GPIO_MODER_MODE9_Pos); //BLUE, PA9
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE4_Msk, 0b01 << GPIO_MODER_MODE4_Pos); //RED, PB4
  MODIFY_REG(GPIOC->MODER, GPIO_MODER_MODE7_Msk, 0b01 << GPIO_MODER_MODE7_Pos); //GREEN, PC7
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE5_Msk, 0b00 << GPIO_MODER_MODE5_Pos); //CENTER, PB5

  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER13_Msk, 0b10 << GPIO_MODER_MODER13_Pos); //alternate fct
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODER14_Msk, 0b10 << GPIO_MODER_MODER14_Pos); //alternate fct

  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE15_Msk, 0b01 << GPIO_MODER_MODER15_Pos);  // output
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE11_Msk, 0b01 << GPIO_MODER_MODER11_Pos);  // output
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7_Msk, 0b01 << GPIO_MODER_MODER7_Pos);    // output
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE12_Msk, 0b01 << GPIO_MODER_MODER12_Pos);  // output

  MODIFY_REG(GPIOB->AFR[1], GPIO_AFRH_AFSEL13_Msk, 0b101 << GPIO_AFRH_AFSEL13_Pos); // AF5
  MODIFY_REG(GPIOB->AFR[1], GPIO_AFRH_AFSEL14_Msk, 0b101 << GPIO_AFRH_AFSEL14_Pos); // AF5

  MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED13_Msk, 0b11 << GPIO_OSPEEDR_OSPEED13_Pos); // high speed
  MODIFY_REG(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED14_Msk, 0b11 << GPIO_OSPEEDR_OSPEED14_Pos); // high speed
   
  SET_BIT(GPIOA->ODR, GPIO_ODR_OD15); // SS output to high
  SET_BIT(GPIOA->ODR, GPIO_ODR_OD11); // SS output to high
  SET_BIT(GPIOB->ODR, GPIO_ODR_OD7);  // SS output to high
  SET_BIT(GPIOB->ODR, GPIO_ODR_OD12); // SS output to high
  
  CLEAR_BIT(GPIOA->ODR, GPIO_ODR_OD15); // SS output to low
}

void initSPI2(SPI_TypeDef *spiHandler) {
  // Set SPI2 off
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_SPE);    

  // Set clock polarity and clock phase to zero
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_CPHA);
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_CPOL);

  // Set master mode
  SET_BIT(spiHandler->CR1, SPI_CR1_MSTR);

  // Set baudrate of max 5Mhz: 16MHz / 32 = 0.5 MHz
  MODIFY_REG(spiHandler->CR1, SPI_CR1_BR_Msk, 0b100 << SPI_CR1_BR_Pos);

  // Set recieve only mode
  SET_BIT(spiHandler->CR1, SPI_CR1_RXONLY);
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_BIDIMODE);
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_BIDIOE);

  // Hardware CRC calculation disable
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_CRCEN);

  // Set software slave management and internal slave select
  SET_BIT(spiHandler->CR1, SPI_CR1_SSI);
  SET_BIT(spiHandler->CR1, SPI_CR1_SSM);

  // Set data frame format to 16 bit
  SET_BIT(spiHandler->CR1, SPI_CR1_DFF);

  // disable ss output
  CLEAR_BIT(spiHandler->CR2, SPI_CR2_SSOE);

  // set spi motorola mode
  CLEAR_BIT(spiHandler->CR2, SPI_CR2_FRF); 
}