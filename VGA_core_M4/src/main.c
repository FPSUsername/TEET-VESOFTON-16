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
//#include "stm32_ub_vga_screen.h"
//#include <math.h>
//#include "draw_API.h"
//#include "error.h"

char *version = "API v0.5";

uint8_t error;

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


	// LCD Write
	LCD_clear();
	LCD_puts("TEET-VESOFTON-16");
	LCD_XY(0, 1);
	LCD_puts(version);
	LCD_cursor_off();

	// LEDs
	int led = 0x00;
	for (int i = 0; i < 8; i++) {
		led = ((led + 1) << 1) - 1;
		LED_put(led);
		DELAY_ms(25);
	}
	LED_put(0x00);

	// UART
	UART_puts(version);
	UART_puts("\n\r");

	// Screen
	UB_VGA_FillScreen(VGA_COL_WHITE);

	// Bitmap
	bitmap(0, 10, 10, 1, &error);
	bitmap(3, 116, 10, 0, &error);
	bitmap(2, 222, 10, 0, &error);

	// Lines
//	line(90,10,90,70,5,"wit", &error); //x1 y1 x2 y2
//	line(210,10,210,70,2,"groen", &error);

//	line(1,1,100,100,4,"rood", &error);
	line(200,35,400,35,4,"zwart", &error);
//	ellipse(200,200,30,40,"blauw", &error);
	ellipse(300,300,100,100,"lichtrood", &error);
//	fill_screen("wit", &error);
//	rectangular(10,10,300,200,"zwart", &error);
//	rectangular(10,10,30,20,"lichtblauw", &error);
//	rectangular(100,100,130,120,"geel", &error);
//	fill_screen("zwart", &error);
	triangle_filled(10,10,130,120,240,200,"lichtmagenta");
	triangle_filled(100,100,30,20,250,250,"cyaan");
	triangle_filled(130,130,17,12,333,133,"lichtgroen");
//	fill_screen("zwart", &error);
//	print_text(10,10,"the quick brown fox jumps over the lazy dog","wit","norm", &error);
//	print_text(10,100,"the quick brown fox jumps over the lazy dog","magenta","vet", &error);
//	print_text(10,200,"the quick brown fox jumps over the lazy dog","lichtcyaan","cursief", &error);

	while(1)
	{
		char **arguments = UART_tokens();
		UART_control(arguments, &error);

		// ALWAYS clear AFTER you are done with your arguments to prevent memory leaks!
		UART_tokens_clear(arguments);
	}
}

