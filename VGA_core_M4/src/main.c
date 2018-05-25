//--------------------------------------------------------------
// File     : main.c
// Datum    : 24.05.2018
// Version  : 0.51
// Author   : UB
// mods by	: J.F. van der Bent, P. Kavvathas, B. Rabenort, N. Koetsveld
// CPU      : STM32F4
// IDE      : Atollic TrueSTUDIO
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "include.h"
//#include "stm32_ub_vga_screen.h"
//#include <math.h>
//#include "draw_API.h"
//#include "error.h"

char *version = "API v0.51";

uint8_t error;

int main(void)
{
	//  uint32_t n;

	// Inits
	SystemInit(); 			// System speed to 168MHz
	LCD_init();
	UART_init();
	LED_init();
	DELAY_init();
	UB_VGA_Screen_Init(); 	// Init VGA-Screen
	START_UP(); 			// Startup screen, LCD output, LED animation
		
	while(1)
	{
		char **arguments = UART_tokens();
		UART_control(arguments, &error);

		// ALWAYS clear AFTER you are done with your arguments to prevent memory leaks!
		UART_tokens_clear(arguments);
	}
}

