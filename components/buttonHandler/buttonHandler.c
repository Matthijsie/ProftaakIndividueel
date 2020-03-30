#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "board.h"
#include "input_key_service.h"
#include "buttonhandler.h"
#include "menu.h"

#define TAG "buttonHandler"

static esp_err_t input_key_service_cb(periph_service_handle_t handle, periph_service_event_t *evt, void *ctx)
{
     if (evt->type == INPUT_KEY_SERVICE_ACTION_CLICK) 
     {
        switch ((int)evt->data) 
        {
            case 1:             //red bttn
                ESP_LOGI(TAG, "[ * ] REC BUTTON PRESSED");
                break;
            case 2:             //set bttn
                ESP_LOGI(TAG, "[ * ] SET BUTTON PRESSED");
                break;
            case 3:             //play bttn
                ESP_LOGI(TAG, "[ * ] PLAY BUTTON PRESSED");
                break;     
            case 4:           //mode bttn
                ESP_LOGI(TAG, "[ * ] MODE BUTTON PRESSED");
                menu_next();
                break;   
            case 5:             //vol down
                ESP_LOGI(TAG, "[ * ] VOL DOWN PRESSED");
                menu_scroll_down();
                break;
            case 6:             //vol up
                ESP_LOGI(TAG, "[ * ] VOL UP PRESSED");
                menu_scroll_up();
                break;
        }
     }
    return ESP_OK;
}

void buttonHandler_init(main_handler_t* main_handler)
{
    ESP_LOGI(TAG, "button_init called");
    input_key_service_info_t input_key_info[] = INPUT_KEY_DEFAULT_INFO();
    periph_service_handle_t input_ser = input_key_service_create(main_handler->set);
    input_key_service_add_key(input_ser, input_key_info, INPUT_KEY_NUM);
    periph_service_set_callback(input_ser, input_key_service_cb, (void *)main_handler->board_handle);
}