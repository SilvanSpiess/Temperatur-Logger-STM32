/**
 * @file mySPI1.c
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Handles the SPI1 connection, used for Sending data 
 *        via the lcd_driver to the LCD_Display.
 */

#include "mySPI1.h"

void initMySPI1() {
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER5_Msk, 0b10 << GPIO_MODER_MODER5_Pos); //alternate fct
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER7_Msk, 0b10 << GPIO_MODER_MODER7_Pos); //alternate fct

  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE6_Msk, 0b01 << GPIO_MODER_MODER6_Pos);  // output
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6_Msk, 0b01 << GPIO_MODER_MODER6_Pos);  // output
  MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE8_Msk, 0b01 << GPIO_MODER_MODER8_Pos);  // output

  MODIFY_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL5_Msk, 0b0101 << GPIO_AFRL_AFSEL5_Pos); // AF5
  MODIFY_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL7_Msk, 0b0101 << GPIO_AFRL_AFSEL7_Pos); // AF7

  // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED5_Msk, 0b11 << GPIO_OSPEEDR_OSPEED5_Pos); // high speed
  // MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED7_Msk, 0b11 << GPIO_OSPEEDR_OSPEED7_Pos); // high speed
}

void initSPI1(SPI_TypeDef *spiHandler) {
  // Set SPI1 off
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_SPE);    

  // Set clock polarity and clock phase to zero
  SET_BIT(spiHandler->CR1, SPI_CR1_CPHA);
  SET_BIT(spiHandler->CR1, SPI_CR1_CPOL);

  // Set baudrate of max 5Mhz: 16MHz / 8 = 2 MHz
  MODIFY_REG(spiHandler->CR1, SPI_CR1_BR_Msk, 0b010 << SPI_CR1_BR_Pos);

  // Set software slave management and internal slave select
  SET_BIT(spiHandler->CR1, SPI_CR1_SSI);
  SET_BIT(spiHandler->CR1, SPI_CR1_SSM);
  // Set master mode
  SET_BIT(spiHandler->CR1, SPI_CR1_MSTR);

  // Hardware CRC calculation disable
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_CRCEN);
  // Set data frame format to 8 bit
  CLEAR_BIT(spiHandler->CR1, SPI_CR1_DFF);
  // disable ss output
  CLEAR_BIT(spiHandler->CR2, SPI_CR2_SSOE);
  // set spi motorola mode
  CLEAR_BIT(spiHandler->CR2, SPI_CR2_FRF); 

  // Set SPI1 on
  SET_BIT(spiHandler->CR1, SPI_CR1_SPE);
}