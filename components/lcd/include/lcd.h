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

typedef struct{
    int x;
    int y;
} Simple_Coordinate;

typedef struct {
    int current_score;
    Simple_Coordinate player_location;
    Simple_Coordinate obstacles[];
} Game_Info;

void lcd_write_menu(MENU_ITEM_STRUCT *menu, int menus_in_loop);
void lcd_write_game(Game_Info *game_info);
void lcd_init();

#endif