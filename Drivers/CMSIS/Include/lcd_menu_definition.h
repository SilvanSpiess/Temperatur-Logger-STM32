/**
  * @file   myCode.h #FIXME: Refactor implementation
  * @author BFH-TI / Andreas HABEGGER <hga3@bfh.ch> 
  * @author BFH-TI / Matthias WAELTI <waltm5@bfh.ch>
  * @author BFH-TI / Daniel DEBRUNNER <dnd1@bfh.ch>
  * @version 1.0.0
  * @date 23.04.2018
  * @brief  #TODO Description missing
  */
#ifndef LCD_MENU_DEFINITION_H
#define LCD_MENU_DEFINITION_H

#include "lcd_menu.h"


/* Submenu LED */
MenuEntry clearLeds = {.description = "Clear LEDs", .type = MENU_EVENT, .event = (menu_event) 9};
MenuEntry redLed = {.description = "Red LED", .type = MENU_EVENT, .event = (menu_event) 2};
MenuEntry greenLed = {.description = "Green LED", .type =  MENU_EVENT, .event = (menu_event) 3};
MenuEntry blueLed = {.description = "Blue blinking LED", .type =  MENU_EVENT, .event = (menu_event)4};
MenuEntry *ledList[] = {&clearLeds, &redLed, &greenLed, &blueLed};
Menu ledMenu = {"Led Menu", 4, ledList};

/* Mein Menu */
MenuEntry first = {.description = "LED toggle on ENTER", .type = MENU_EVENT, .event = (menu_event) 5};
MenuEntry second = {.description = "LED toggle on EXIT", .type = MENU_EVENT, .event = (menu_event) 6};
MenuEntry third = {.description = "Pot1,2 to USART", .type = MENU_EVENT, .event = (menu_event) 7};
MenuEntry fourth = {.description = "Pot1 Pot2", .type = MENU_EVENT, .event = (menu_event) 8};
MenuEntry led  = {.description = "Led", .type = MENU_SUBMENU, .submenu = &ledMenu};
MenuEntry ledClear  = {.description = "Led Clear all", .type = MENU_EVENT, .event = (menu_event) 9};
MenuEntry CANbus  = {.description = "CAN-bus", .type = MENU_EVENT, .event = (menu_event) 10};

MenuEntry *mainList[] = {&first, &second, &third, &fourth, &led, &ledClear, &CANbus};
Menu mainMenu = {"Main Menu", 7, mainList};

#endif // LCD_MENU_DEFINITION_H
