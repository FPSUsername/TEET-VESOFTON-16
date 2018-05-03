//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.1
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

char *version = "Version: 1.0";

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz
	LCD_init();
	UART_init();
	DELAY_init();

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_GREEN);
	UB_VGA_SetPixel(10,10,10);
	LCD_puts("TEET VESOFTON 16");
//	LCD_set
	LCD_puts(version);

	while(1)
	{
		// put the code here'
		print_error();
		DELAY_s(5);
	}
}

