#ifndef mainHandler_H
#define mainHandler_H

#include "esp_peripherals.h"
#include "esp_wifi.h"
#include "board.h"
#include "periph_wifi.h"

typedef struct{
    esp_periph_set_handle_t set;
    audio_board_handle_t board_handle;
    esp_periph_handle_t wifi_handler;
} main_handler_t;

void mainHandler_init(main_handler_t * main_handler);

#endif