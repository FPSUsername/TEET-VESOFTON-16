/**
  *
  *@file    	main.c
  * @author 	UB, J.F. van der Bent, P. Kavvathas, B. Rabenort, N. Koetsveld
  * @version	V0.51
  * @date   	24-Mei-2018
  * @brief  	Main
  *
  * \n CPU      : STM32F4\n
 	IDE      : Atollic TrueSTUDIO\n
	Module   : CMSIS_BOOT, M4_CMSIS_CORE\n
	Function : VGA_core DMA LIB 320x240, 8bit color\n
  *
  */

#include "main.h"
#include "include.h"
#include "Doxygen.c"
//#include "stm32_ub_vga_screen.h"
//#include <math.h>
//#include "draw_API.h"
//#include "error.h"

<<<<<<< HEAD
/**
 * Version number for displaying
 */
=======

>>>>>>> master
char *version = "API v0.51";

/**
 * Int for error codes
 */
uint8_t error;

/** @brief	Main code
 *
 * Initialization and main loop for getting code from the UART
 */
int main(void)
{
//	  uint32_t n;
	uint8_t error;

	// Inits
	SystemInit(); 			// System speed to 168MHz
	LCD_init();
	UART_init();
	LED_init();
	DELAY_init();
<<<<<<< HEAD
	UB_VGA_Screen_Init(); 	// Init VGA-Screen
	START_UP(); 			// Startup screen, LCD output, LED animation
		
=======
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
	UB_VGA_FillScreen(VGA_COL_LIGHT_GREEN);

	/* Initial setup */

	// Bitmap
	bitmap(0, 10, 10, 1, &error);
	bitmap(3, 116, 10, 0, &error);
	bitmap(2, 222, 10, 0, &error);

	// Lines
	line(70,10,100,70,5,"wit", &error); //x1 y1 x2 y2
	line(10,190,300,190,2,"lichtblauw", &error);

	// Text
	print_text(0, 80, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "blauw", "norm", &error);
	print_text(0, 90, "abcdefghijklmnopqrstuvwxyz", "groen", "cursief", &error);
	print_text(0, 100, "~`!@#$%^&*()-_=+{}[]:;',.<>/?|", "cyaan", "vet", &error);
	print_text(0, 110, "1234567890", "rood", "norm", &error);
	print_text(0, 120, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", "paars", "norm", &error);

	// Greek
	print_text(0, 140, "*!+'30", "zwart", "greek", &error);
	print_char(56, 140, 37, "zwart", "greek", &error);
	print_text(62, 140, "1!", "zwart", "greek", &error);
//	print_text(0, 150, "1234567890!#$&*()-+',.>", "zwart", "greek");

	// Ellipse
	ellipse_filled(55, 190, 10, 30, "rood", &error);
	ellipse(55,190,40,30,"wit", &error);

	// Rectangulars
	rectangular(110,160,60,70,"blauw", &error);
	rectangular_thick(120,170,40,50,5,5,"groen", &error);
	rectangular_filled(130,180,20,30,"geel", &error);

	// Triangle
	triangle(200, 160, 260, 230, 200, 230, "paars");
	triangle_filled(270, 230, 269, 150, 200, 150, "rood");

	/* Initial setup end */

>>>>>>> master
	while(1)
	{
		char **arguments = UART_tokens();
		UART_control(arguments, &error);

		/** ALWAYS clear AFTER you are done with your arguments to prevent memory leaks! */
		UART_tokens_free(arguments);
	}
}

