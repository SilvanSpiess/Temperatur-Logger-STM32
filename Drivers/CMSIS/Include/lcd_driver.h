/**
  * @file   lcd_driver.h
  * @author BFH-TI / Andreas HABEGGER <hga3@bfh.ch> #FIXME: Refactor implementation
  * @author BFH-TI / Matthias WAELTI <waltm5@bfh.ch>
  * @author BFH-TI / Daniel DEBRUNNER <dnd1@bfh.ch>
  * @author BFH-TI / Kernen MICHA <knm7@bfh.ch>
  * @version 1.0.0
  * @version 0.5
  * @date 08.10.2019
  * @date 21.04.2018
  * @brief  Driver for the NHD-C12832A1Z-FSW-FBW-3V3 LCD display.
  * @hardware NucleoF446RE, NHD-C12832A1Z-FSW-FBW-3V3, mbed-016.1-application-shield
  * @hardware 2D5 Printer
  */

#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#ifdef __cplusplus
 extern "C" {
#endif

//#include "main.h"
// #include "spi.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum{LCD_FONT_8, LCD_FONT_24, LCD_NUMBER_OF_FONTS}lcd_fontSize;

typedef enum{LCD_MENU_SYMBOL, LCD_PLAY_SYMBOL, LCD_STANDING_MAN,
             LCD_RUNNING_MAN, LCD_NUMBER_OF_SYMBOLS}lcd_symbol;

/**
 * @brief Initialization function to wake up the display.
 */
void lcd_init(void);

/**
 * @brief Function to clear the lcd buffer.
 */
void lcd_clear(void);

/**
 * @brief Function to write the lcd buffer to the display.
 */
void lcd_show(void);

/**
 * @brief Function to write a string to the display buffer.
 * @param x                     X coordinate of the string origin.
 * @param y                     Y coordinate of the string origin.
 * @param s                     String to write.
 * @param                       size  Font size as enum of lcd_fontSize.
 * @param contrastIsInverted    Contrast inversion.
 */
void lcd_setString(uint8_t x, uint8_t y, const char *string, uint8_t size , bool contrastIsInverted);

/**
 * @brief Function to write a single pixel to the display buffer.
 * @param xPosition     X coordinate of the string origin.
 * @param yPosition     Y coordinate of the string origin.
 * @param pixelIsSet    Contrast set or reset.
 */
void lcd_setPixel(uint8_t xPosition, uint8_t yPosition, bool pixelIsSet);

/**
 * @brief Function to adjust the display contrast.
 * @param electronicVolume  Contrast value from 0 to 63.
 */
void lcd_setContrast(uint8_t electronicVolume);

/**
 * @brief Function to write a frame to the display buffer.
 * @param xPositionUL   X coordinate of the upper left edge.
 * @param yPositionUL   Y coordinate of the upper left edge.
 * @param xPositionDR   X coordinate of the down right edge.
 * @param yPositionDR   Y coordinate of the down right edge.
 */
void lcd_setFrame(uint8_t xPositionUL, uint8_t yPositionUL, uint8_t xPositionDR, uint8_t yPositionDR);

/**
 * @brief Function to write a bar to the display buffer.
 * @param xPositionUL   X coordinate of the upper left edge.
 * @param yPositionUL   Y coordinate of the upper left edge.
 * @param xPositionDR   X coordinate of the down right edge.
 * @param yPositionDR   Y coordinate of the down right edge.
 */
void lcd_setBar(uint8_t xPositionUL, uint8_t yPositionUL, uint8_t xPositionDR, uint8_t yPositionDR);

/**
 * @brief Function to write a special or user defined symbol to the display buffer.
 * @param xPosition             X coordinate of the symbol origin.
 * @param yPosition             Y coordinate of the symbol origin.
 * @param symbol                Symbol to set from the lcd_symbol.h file.
 * @param contrastIsInverted    Contrast inversion.
 */
void lcd_setSymbol8(uint8_t xPosition, uint8_t yPosition, lcd_symbol symbol, bool contrastIsInverted);

/**
* @brief Function to write a straight line into the display buffer
*/
void lcd_setLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t state);

/**
 * @brief Function to write a straight line into the display buffer
 * @param x,y                   Corner point of a rectangle
 * @param w                     Horizonal width of the rectangle
 * @param h                     Vertical Height of the rectangle
 */
void lcd_setRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t state);

void lcd_setBackgroundLight(bool value);


#ifdef __cplusplus
}
#endif

#endif /* LCD_DRIVER_H */
