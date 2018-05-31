/**
  *
  *@file    	logic_layer.c
  * @author 	P. Kavvathas
  * @version	V0.4
  * @date   	24-Mei-2018
  * @brief  	Logic layer
  *
  * \n Compares input string from the user with predefined functions
  *
  */

#include "include.h"

extern uint8_t error; /** Error handler, defined either in main.c or error.c */

/**
 * \section UART control
 * This function will call the functions by comparing the input string with the corresponding name of the predefined functions
 */
void UART_control(char **array, uint8_t *perr)
{
	error = 0; /** Reset error status */

	/** Functions */
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
		if (array[4] == NULL)
			array[4] = 0; /** Disable transparency if not defined */
		bitmap(atoi(array[1]), atoi(array[2]), atoi(array[3]), atoi(array[4]), &error);
	}
	else if (strcmp(array[0], "wacht") == 0)			DELAY(atoi(array[1]), &error);
	else if (strcmp(array[0], "clearscherm") == 0)		fill_screen(array[1], &error);
	else { /** Error, function does not exist */
		*perr = ERR_INPUT_INVALID;
		pError(*perr);
	}
}
