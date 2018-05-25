//-----------------------------
// File     : ui.c
// Datum    : 11.05.2018
// Version  : 0.31
// Author   : P. Kavvathas
// Mods by	: N. Koetsveld
//-----------------------------

#include "ui.h"
#include "main.c"
#include "include.h"
//#include "draw_API.h"
//#include "error.h"

extern uint8_t error;

/* Get input commands, split them and return them
 * Call UART_tokens_clear() after calling this function
 */
char ** UART_tokens()
{
	char **array = NULL; // By using NULL, the first time realloc will run, it will act as a malloc function.

	unsigned char i = 0;
	char *str = (char *) malloc(255); // Allocate memory for the input buffer
	UART_gets(str, 1); // Grab terminal input commands

	#ifdef DEBUG
	UART_puts("UART_tokens function:\n");
	UART_puts("Nr:\tUART\tArray\n");
	#endif

	// Extract each variable from the input buffer
	for (char* p = strtok(str, ","); p != NULL; p = strtok(NULL, ",")) {
		// Write to a new buffer
		array = realloc(array, (i + 1) * sizeof(char*)); // Dynamically increase the size of the array
		array[i] = strlwr(strdup(p)); // Lowercase the string and copy it

		#ifdef DEBUG
		UART_putint(i); // Array iteration
		UART_puts("\t");
		UART_puts(p); // Input on UART
		UART_puts("\t");
		UART_puts(array[i]); // Copy to array
		UART_puts("\n");
		#endif

		i++;
	}

	array[i] = NULL; // Add Null to the end so you can easily iterate; check the cleararray() function

	free(str); // Input buffer isn't needed anymore
	str = NULL;

	return array;
}

/* Clears the input commands array to prevent memory leaks
 * Always call this function when you're done with the array.
 */
void UART_tokens_clear(char **array)
{
	for(unsigned char i = 0; array[i] != NULL; i++)
	    free(array[i]);
	free(array);
}


/* UART control
 * This function will call the functions
 */
void UART_control(char **array, uint8_t *perr)
{
	error = 0; // Reset error status
	if 		(strcmp(array[0], "lijn") == 0)				line(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), array[6], &error);
	else if (strcmp(array[0], "arrow") == 0)			arrow(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), array[6], &error);
	else if (strcmp(array[0], "ellips") == 0)			ellipse(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5], &error);
	else if (strcmp(array[0], "ellips_gevuld") == 0)	ellipse_filled(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5], &error);
	else if (strcmp(array[0], "rechthoek") == 0)		rectangular(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5], &error);
	else if (strcmp(array[0], "rechthoek_dik") == 0)	rectangular_thick(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), atoi(array[6]), array[7], &error);
	else if (strcmp(array[0], "rechthoek_gevuld") == 0)	rectangular_filled(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5], &error);
	else if (strcmp(array[0], "driehoek") == 0)			triangle(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), atoi(array[6]), array[7]);
	else if (strcmp(array[0], "driehoek_gevuld") == 0)	triangle_filled(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), atoi(array[6]), array[7]);
	else if (strcmp(array[0], "letter") == 0)			print_char(atoi(array[1]), atoi(array[2]), atoi(array[3]), array[4], array[5], &error);
	else if (strcmp(array[0], "tekst") == 0)			print_text(atoi(array[1]), atoi(array[2]), array[3], array[4], array[5], &error);
	else if (strcmp(array[0], "bitmap") == 0) {
		if (array[4] == NULL) array[4] = 0; // Disable transparency if not defined
		bitmap(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), &error);
	}
	else if (strcmp(array[0], "wacht") == 0)			DELAY(atoi(array[1]), &error);
	else if (strcmp(array[0], "clearscherm") == 0)		fill_screen(array[1], &error);
	else { // Error, function does not exist
		*perr = ERR_INPUT_INVALID;
		pError(*perr);
	}
}

/* Start-up
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

