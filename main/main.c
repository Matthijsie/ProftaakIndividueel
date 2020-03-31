#include "mainHandler.h"
#include "menu.h"
#include "buttonhandler.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main()
{
	main_handler_t main_handler;
    mainHandler_init(&main_handler);
    buttonHandler_init(&main_handler);
    menu_init();

    while(1)
    {
        vTaskDelay(60 * 1000 / portTICK_RATE_MS);
    }
}