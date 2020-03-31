#include "esp_log.h"
#include "game.h"
#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "game"
#define GAME_TICKS_PER_SECOND 4
#define MAX_JUMP_HEIGHT 1
#define JUMP_TIME_SECONDS 2

Game_Info* game_info;

void main_game_task(void* pvParameters);

void game_start()
{
    ESP_LOGI(TAG, "game started!");
    game_info = malloc(sizeof(Game_Info));
    
    Simple_Coordinate player_location_struct = {1,2};
    game_info->player_location = player_location_struct;

    xTaskCreate(main_game_task, "Game_Task", 3*1024, NULL, 1, NULL);
}

unsigned int game_stop()
{
    game_is_running = false;
    unsigned int highscore = game_info->current_score;
    free(game_info);
    return highscore;
}

void game_jump()
{
    game_info->player_location.y -= MAX_JUMP_HEIGHT;
    vTaskDelay(JUMP_TIME_SECONDS * 1000 / portTICK_RATE_MS);
    game_info->player_location.y += MAX_JUMP_HEIGHT;
}

void main_game_task(void* pvParameters)
{
    game_is_running = true;
    while (game_is_running)
    {
        lcd_write_game(game_info);
        vTaskDelay((1000 / GAME_TICKS_PER_SECOND) / portTICK_RATE_MS);
    }

    vTaskDelete(NULL);
}