#include "mainHandler.h"
#include "lcd.h"

void app_main()
{
	main_handler_t main_handler;
    mainHandler_init(&main_handler);
    lcd_init();
}