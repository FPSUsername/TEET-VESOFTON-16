/**
  *
  *@file    	front_layer.c
  * @author 	P. Kavvathas
  * @version	V0.4
  * @date   	24-Mei-2018
  * @brief  	Front layer
  *
  * \n
  *
  */


#include "include.h"

/** 
 * \section UART tokens
 * Get input commands, split them and return them
 * Call UART_tokens_clear() after calling this function
 */
char ** UART_tokens()
{
	char **array = NULL; /** By using NULL, the first time realloc will run, it will act as a malloc function. */

	unsigned char i = 0;
	char *str = (char *) malloc(255); /** Allocate memory for the input buffer */
	UART_gets(str, 1); /** Grab terminal input commands */

	#ifdef DEBUG
	UART_puts("UART_tokens function:\n");
	UART_puts("Nr:\tUART\tArray\n");
	#endif

	/** Extract each variable from the input buffer */
	for (char* p = strtok(str, ","); p != NULL; p = strtok(NULL, ",")) {
		/** Write to a new buffer */
		array = realloc(array, (i + 1) * sizeof(char*)); /** Dynamically increase the size of the array */
		array[i] = strlwr(strdup(p)); /** Lowercase the string and copy it */

		#ifdef DEBUG
		UART_putint(i); /** Array iteration */
		UART_puts("\t");
		UART_puts(p); /** Input on UART */
		UART_puts("\t");
		UART_puts(array[i]); /** Copy to array */
		UART_puts("\n");
		#endif

		i++;
	}

	array[i] = NULL; /** Add Null to the end so you can easily iterate; check the cleararray() function */

	free(str); /** Input buffer isn't needed anymore */
	str = NULL;

	return array;
}

/**
 * \section UART tokens clear
 * Frees the input commands array to prevent memory leaks
 * Always call this function when you're done with the array.
 */
void UART_tokens_free(char **array)
{
	/** Free each member of the array and then free the array itself */
	for(unsigned char i = 0; array[i] != NULL; i++)
	    free(array[i]);
	free(array);
}
