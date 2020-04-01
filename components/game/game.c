#include "esp_log.h"
#include "game.h"
#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>
#include "menu.h"

#define TAG "game"
#define GAME_TICKS_PER_SECOND 4         ///< Determines how often the game updates every seconds
#define MAX_JUMP_HEIGHT 1               ///< How many cells high the player jumps
#define JUMP_TIME_SECONDS 1             ///< The amount of time the player stays in the air

// Variables
Game_Info* game_info;                   ///< Pointer to memory adress of game information struct

// Prototypes
void game_main_task(void* pvParameters);

void game_start()
{
    ESP_LOGI(TAG, "Initlializing game resources");
    game_info = malloc(sizeof(Game_Info));

    game_info->player_location.x = 1;
    game_info->player_location.y = 2;
    game_info->current_score = 0;
    game_info->obstacle.y = 2;
    game_info->obstacle.x = 20;

    ESP_LOGI(TAG, "Starting game!");
    xTaskCreate(game_main_task, "Game_Task", 3*1024, NULL, 1, NULL);
}

void game_stop()
{
    game_is_running = false;
    unsigned int score = game_info->current_score;
    ESP_LOGI(TAG, "Game ended with score %d", (int)score);
    free(game_info);
    menu_add_score(score);
    menu_next();
}

void game_jump()
{
    ESP_LOGI(TAG, "Jump");
    game_info->player_location.y -= MAX_JUMP_HEIGHT;
    vTaskDelay(JUMP_TIME_SECONDS * 1000 / portTICK_RATE_MS);
    game_info->player_location.y += MAX_JUMP_HEIGHT;
}

/**
 * @brief Main game loop, updates obstacles, score and checks if the player isn't colloiding with an obstacle
 * 
 */ 
void game_main_task(void* pvParameters)
{
    game_is_running = true;

    do 
    {   
        //Update the location of the obstacles 
        if (game_info->obstacle.x -1 < 0)
        {
            game_info->current_score++;
            game_info->obstacle.x = 20;
        }else
        {
            game_info->obstacle.x -= 1;
        }
        

        //Finish the game if player hits an obstacle
        if (game_info->obstacle.x == game_info->player_location.x && game_info->obstacle.y == game_info->player_location.y)
        {
            game_stop();
            break;
        }
        
        lcd_write_game(game_info);
        vTaskDelay((1000 / GAME_TICKS_PER_SECOND) / portTICK_RATE_MS);
    }while (game_is_running);
    

    //Delete this task once the game has ended
    vTaskDelete(NULL);
}