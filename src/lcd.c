/**
 * @file lcd.c
 * @ref <TemperatureLogger>
 * @author Silvan Spiess <silvan.spiess@bfh-student.ch>
 * @author Allemann <sarah.allemann@bfh-student.ch>
 * @copyright Bern University of Applied Sciences
 *            Silvan Spiess, Sarah Allemann 
 * @version v1.0.0
 * @date 11. Jan. 2024
 * 
 * @brief Initialises LCD_Display as well as maintains its handles it 
 * during runtime of the program.
 */

#include "lcd.h"

void screenSetup() {
  lcd_setFrame(0, 0, 127, 31);
  lcd_setString(43, 5, "WELCOME!", LCD_FONT_8, 0);
  lcd_setString(38, 20, "loading.", LCD_FONT_8, 0);
  lcd_show();
  for(uint32_t i = 5000000; i; i--);
  lcd_setString(85, 20, ".", LCD_FONT_8, 0);
  lcd_show();
  for(uint32_t i = 5000000; i; i--);
  lcd_setString(90, 20, ".", LCD_FONT_8, 0);
  lcd_show();
  lcd_clear(); 
  lcd_setFrame(0, 0, 127, 31);
  for(uint32_t i = 3000000; i; i--);
}

void initialScreen() {
  lcd_setFrame(0, 0, 127, 31);
  lcd_setString(10, 20, "Channel1", LCD_FONT_8, 0);
  lcd_setString(70, 20, "Channel2", LCD_FONT_8, 0);
  lcd_show();
}

void updateScreen(uint16_t te_1, uint16_t te_2, uint16_t ch_1, uint16_t ch_2, uint16_t isOn) {
  lcd_clear();
  lcd_setFrame(0, 0, 127, 31);
  lcd_setString(10, 20, "Channel1", LCD_FONT_8, 0);
  lcd_setString(70, 20, "Channel2", LCD_FONT_8, 0);

  // if(!isOn) {
  //   lcd_show();
  //   return;
  // }
  if(!ch_1 && !ch_2) {
    lcd_setString(26, 5, "OFF", LCD_FONT_8, 0);
    lcd_setString(85, 5, "OFF", LCD_FONT_8, 0);
    lcd_show();
    return;
  }
  if(ch_1) {
    if(te_1 < 1000) {
      char str[5];
      sprintf(str, "%d", te_1);
      lcd_setString(26, 5, str, LCD_FONT_8, 0);
    }      
    else 
      lcd_setString(26, 5, "ERR", LCD_FONT_8, 0);    
  }
  if(!ch_1)
      lcd_setString(26, 5, "OFF", LCD_FONT_8, 0);
  if(ch_2) {
    if(te_2 < 1000){
      char str[5];
      sprintf(str, "%d", te_2);
      lcd_setString(85, 5, str, LCD_FONT_8, 0);
    }      
    else 
      lcd_setString(85, 5, "ERR", LCD_FONT_8, 0);    
  }
  if(!ch_2)
      lcd_setString(85, 5, "OFF", LCD_FONT_8, 0);
  lcd_show();
}