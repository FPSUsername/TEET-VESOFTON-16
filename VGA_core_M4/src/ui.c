//-----------------------------
// File     : ui.c
// Datum    : 11.05.2018
// Version  : 0.3
// Author   : P. Kavvathas
//-----------------------------

#include "ui.h"
#include "include.h"
#include "draw_API.h"
#include <ctype.h>


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
void UART_control(char **array)
{
	uint8_t err = 0;

	if 		(strcmp(array[0], "lijn") == 0)				err = line(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), array[6]);
	else if (strcmp(array[0], "arrow") == 0)			err = arrow(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), array[6]);
	else if (strcmp(array[0], "ellips") == 0)			err = ellipse_filled(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5]);
	else if (strcmp(array[0], "ellips_gevuld") == 0)	err = ellipse_filled(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5]);
	else if (strcmp(array[0], "rechthoek") == 0)		err = rectangular(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5]);
	else if (strcmp(array[0], "rechthoek_dik") == 0)	err = rectangular_thick(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), atoi(array[6]), array[7]);
	else if (strcmp(array[0], "rechthoek_gevuld") == 0)	err = rectangular_filled(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), array[5]);
	else if (strcmp(array[0], "driehoek") == 0)			err = triangle(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), atoi(array[5]), atoi(array[6]), array[7]);
	else if (strcmp(array[0], "letter") == 0)			err = print_char(atoi(array[1]), atoi(array[2]), atoi(array[3]), array[4], array[5]);
	else if (strcmp(array[0], "tekst") == 0)			err = print_text(atoi(array[1]), atoi(array[2]), array[3], array[4], array[5]);
	else if (strcmp(array[0], "bitmap") == 0) {
		if (array[4] == NULL) array[4] = 0; // Disable transparency if not defined
		err = bitmap(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]));
	}
	else if (strcmp(array[0], "wacht") == 0)			err = DELAY(atoi(array[1]));
	else if (strcmp(array[0], "clearscherm") == 0)		err = fill_screen(array[1]);
	else UART_puts("Invalid command!\n");

	if (err != 0){
		UART_puts("\nReturn code: ");
		UART_putint(err);
		UART_puts("\n");
	}
}
