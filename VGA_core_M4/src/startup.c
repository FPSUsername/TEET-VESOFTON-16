/**
  *
  * @file    	startup.c
  * @author 	P. Kavvathas, B. Rabenort, N. Koetsveld
  * @version	V0.5
  * @date   	24-Mei-2018
  * @brief  	Initializing the start screen
  *
  * \n \n Shows some of the functions including:
  * - Three bitmaps
  * - line
  * - Printing text on screen
  * - Filled and empty ellipse
  * - Filled, thick and empty retangular
  * - Filled and empty triangle
  */

#include "include.h"
#include "main.c"

/** Start-up
 * Function to make a start screen with LCD output and LED animation
 */
void START_UP(void)
{
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
}
