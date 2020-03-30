#ifndef LCD_H
#define LCD_H

#include <stdbool.h>

typedef struct{
    int id;
    int nextid;
    char menu_name[17];
    char line1[21];
    char line2[21];
    char line3[21];
    int scrollable;
} MENU_ITEM_STRUCT;

void lcd_write_menu(MENU_ITEM_STRUCT *menu, int menus_in_loop);
void lcd_init();

#endif