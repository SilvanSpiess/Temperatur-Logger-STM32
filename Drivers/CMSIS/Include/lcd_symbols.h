/**
  * @file   lcd_driver.h
  * @author BFH-TI / Andreas HABEGGER <hga3@bfh.ch>
  * @author BFH-TI / Matthias WAELTI <waltm5@bfh.ch>
  * @author BFH-TI / Daniel DEBRUNNER <dnd1@bfh.ch>
  * @author BFH-TI / Kernen MICHA <knm7@bfh.ch>
  * @version 1.0.0
  * @date   21.04.2018
  * @brief  Symbol file for the lcd_driver library.
  */


#ifndef LCD_SYMBOLS_H
#define LCD_SYMBOLS_H

const uint16_t lcd_symbols[] = {
    /* Menu Symbol */
    0x1D, 0x00, 0x1D, 0x00, 0x1D, 0x00, 0x1D, 0x00,
    /* Play Symbol */
    0x02, 0x06, 0x0E, 0x1E, 0x0E, 0x06, 0x02, 0x00,
    /* Standing Man */
    0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06,
    /* Walking Man 1 */
    0x06, 0x06, 0x00, 0x0E, 0x07, 0x06, 0x0B, 0x19
};

#endif // LCD_SYMBOLS_H
