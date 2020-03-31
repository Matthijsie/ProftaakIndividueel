#include "lcd.h"
#include "menu.h"
#include "esp_log.h"
#include <string.h>
#include "game.h"

#define TAG "menu"
#define MENU_MAIN_1 0
#define MENU_MAIN_2 1
#define MAIN_MENU_AMOUNT 2

#define MAX_HIGHSCORE_SLOTS 5
#define MENU_MAIN_1_ITEMS 3

void menu_scroll_helper(char** menu_items, int arr_size, int modifier);

int menu_state;
int scroll_state;

char *game_menu[MENU_MAIN_1_ITEMS] = {"Start","Reset Highscores", "Quit"};
char *highscore_menu[MAX_HIGHSCORE_SLOTS] = {"<Empty>", "<Example>", "<Empty>", "<Empty>", "<Empty>"};

MENU_ITEM_STRUCT menus[] = 
{
    //id, nextid, name, line1, line2, line3, scrollable
    {
        MENU_MAIN_1,
        MENU_MAIN_2,
        "Game",
        "",
        "",
        "",
        true
    },
    {
        MENU_MAIN_2,
        MENU_MAIN_1,
        "Highscores",
        "",
        "",
        "",
        true
    }   
};

void menu_init()
{
    ESP_LOGI(TAG, "menu_init");
    lcd_init();
    menu_state = 0;
    scroll_state = 0;

    strcpy(menus[MENU_MAIN_1].line1, game_menu[0]);
    strcpy(menus[MENU_MAIN_1].line2, game_menu[1]);
    strcpy(menus[MENU_MAIN_1].line3, game_menu[2]);

    strcpy(menus[MENU_MAIN_2].line1, highscore_menu[0]);
    strcpy(menus[MENU_MAIN_2].line2, highscore_menu[1]);
    strcpy(menus[MENU_MAIN_2].line3, highscore_menu[2]);

    lcd_write_menu(&menus[menu_state], MAIN_MENU_AMOUNT);
}

void menu_next()
{
    ESP_LOGI(TAG, "menu_next");
    menu_state = menus[menu_state].nextid;
    scroll_state = 0;
    lcd_write_menu(&menus[menu_state], MAIN_MENU_AMOUNT);
}

void menu_scroll_down()
{
    ESP_LOGI(TAG, "menu_scroll_down");
    if (menus[menu_state].scrollable == true)   //Check if the current menu is scrollable
    {
        int arr_size;
        switch (menu_state)
        {
        case MENU_MAIN_1:
            arr_size = (sizeof(game_menu) / sizeof(game_menu[0]));  //Calculate Array size
            menu_scroll_helper(game_menu, arr_size, 1);
            break;
        
        case MENU_MAIN_2:
            arr_size = (sizeof(highscore_menu) / sizeof(highscore_menu[0]));  //Calculate Array size
            menu_scroll_helper(highscore_menu, arr_size, 1);
            break;
        }
        lcd_write_menu(&menus[menu_state], MAIN_MENU_AMOUNT);
    }
}

void menu_scroll_up()
{
    ESP_LOGI(TAG, "menu_scroll_up");
    if (menus[menu_state].scrollable == true)   //Check if the current menu is scrollable
    {
        int arr_size;
        switch (menu_state)
        {
        case MENU_MAIN_1:
            arr_size = (sizeof(game_menu) / sizeof(game_menu[0]));  //Calculate Array size
            menu_scroll_helper(game_menu, arr_size, -1);
            break;
        
        case MENU_MAIN_2:
            arr_size = (sizeof(highscore_menu) / sizeof(highscore_menu[0]));  //Calculate Array size
            menu_scroll_helper(highscore_menu, arr_size, -1);
            break;
        }

        lcd_write_menu(&menus[menu_state], MAIN_MENU_AMOUNT);
    }
}

void menu_select_item()
{
    int arr_size;
    switch (scroll_state)
    {
    case 0:
        game_is_running ? : game_start();
        break;
    case 1:
        arr_size = (sizeof(game_menu) / sizeof(game_menu[0]));  //Calculate Array size
        for (size_t i = 0; i < arr_size; i++)
        {
            strcpy(highscore_menu[i], "<empty>");
        }
        break;
    case 2:
        ESP_LOGI(TAG, "Can't quit quite yet!");
        break;
    }    
}

void menu_scroll_helper(char** menu_items, int arr_size, int modifier)
{
    //Calculate new scroll state
    scroll_state = (scroll_state + modifier + arr_size) % arr_size;

    //Change the strings in the menu structs and return them to start if it exceeds the max array size
    strcpy(menus[menu_state].line1, menu_items[scroll_state]);
    strcpy(menus[menu_state].line2, menu_items[(scroll_state + 1) % arr_size]);
    strcpy(menus[menu_state].line3, menu_items[(scroll_state + 2) % arr_size]);
}