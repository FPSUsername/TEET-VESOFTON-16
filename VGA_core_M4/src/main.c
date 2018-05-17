//--------------------------------------------------------------
// File     : main.c
// Datum    : 11.05.2018
// Version  : 0.3
// Author   : UB
// mods by	: J.F. van der Bent, P. Kavvathas
// CPU      : STM32F4
// IDE      : Atollic TrueSTUDIO
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "include.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "draw_API.h"

char *version = "API v0.4";

int main(void)
{
	//  uint32_t n;

	// Inits
	SystemInit(); // System speed to 168MHz
	LCD_init();
	UART_init();
	LED_init();
	DELAY_init();
	UB_VGA_Screen_Init(); // Init VGA-Screen

	// LEDs
	LED_put(0xFF);
	DELAY_ms(500);
	LED_put(0x00);

	// Screen
	UB_VGA_FillScreen(VGA_COL_BLACK);
	bitmap(0, 10, 10);
	bitmap(1, 116, 10);
	bitmap(2, 222, 10);
	ellipse_filled(42, 175, 10, 30, "rood");
//	ellipse_filled(300,300,40,30,"lichtrood");
//	line(80,80,120,120,30,"wit"); //x1 y1 x2 y2
//	line(120,80,80,120,9,"groen");
	rectangular(75,150,50,75,"blauw");
	rectangular_thick(150,150,75,50,5,5,"groen");
	rectangular_filled(230,150,75,75,"geel");


	// LCD Write
	LCD_clear();
	LCD_puts("TEET-VESOFTON-16");
	LCD_XY(0, 1);
	LCD_puts(version);
	LCD_cursor_off();

	// UART
	UART_puts(version);
	UART_puts("\n\r");

	while(1)
	{
		// How to call UART_tokens
		char **arguments = UART_tokens();

		// Iterate through the arguments and print them (Example code)
//		for(unsigned char i = 0; arguments[i] != NULL; i++)
//		{
//			UART_puts(arguments[i]);
//			UART_puts("\n");
//		}

		UART_control(arguments);

		// ALWAYS clear AFTER you are done with your arguments to prevent memory leaks!
		UART_tokens_clear(arguments);
	}
}

