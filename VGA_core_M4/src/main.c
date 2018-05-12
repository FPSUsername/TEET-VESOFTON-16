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

char *version = "API UART v0.31";

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
	UB_VGA_FillScreen(VGA_COL_GREEN);
	UB_VGA_SetPixel(10,10,10);

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
		for(unsigned char i = 0; arguments[i] != NULL; i++)
		{
			UART_puts(arguments[i]);
			UART_puts("\n");
		}

		// ALWAYS clear AFTER you are done with your arguments to prevent memory leaks!
		UART_tokens_clear(arguments);
	}
}

