#include "lcd.h"
#include "menu.h"
#include "esp_log.h"

#define TAG "menu"

int menu_state;
int scroll_state;
int menus_in_loop = 2;

MENU_ITEM_STRUCT menus[] = 
{
    //id, nextid, name, line1, line2, line3, scrollable
    {
        0,
        1,
        "Game",
        "Start",
        "",
        "",
        true
    },
    {
        1,
        0,
        "Highscores",
        "<empty>",
        "<empty>",
        "<empty>",
        true
    }
};

void menu_init()
{
    ESP_LOGI(TAG, "menu_init");
    lcd_init();
    menu_state = 0;
    scroll_state = 0;

    lcd_write_menu(&menus[menu_state], menus_in_loop);
}

void menu_next()
{
    ESP_LOGI(TAG, "menu_next");
    menu_state = menus[menu_state].nextid;
    scroll_state = 0;
    lcd_write_menu(&menus[menu_state], menus_in_loop);
}

void menu_scroll_down()
{
    ESP_LOGI(TAG, "menu_scroll_down");
    if (menus[menu_state].scrollable == true)   //Check if the current menu is scrollable
    {
        
    }
}

void menu_scroll_up()
{
    ESP_LOGI(TAG, "menu_scroll_up");
    if (menus[menu_state].scrollable == true)   //Check if the current menu is scrollable
    {
        
    }
}