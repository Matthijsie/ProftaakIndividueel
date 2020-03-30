#include "mainHandler.h"
#include "menu.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "buttonhandler.h"

void app_main()
{
	main_handler_t main_handler;
    mainHandler_init(&main_handler);
    buttonHandler_init(&main_handler);
    menu_init();
}