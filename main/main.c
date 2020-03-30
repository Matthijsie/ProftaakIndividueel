#include "mainHandler.h"
#include "menu.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main()
{
	main_handler_t main_handler;
    mainHandler_init(&main_handler);
    menu_init();

    while (1)
    {
        menu_next();
        vTaskDelay(2000/portTICK_RATE_MS);
    }
}