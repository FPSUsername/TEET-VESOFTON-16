/**
* File     : error.c
* Datum    : 24.05.2018
* Version  : 0.1
* Author   : N. Koetsveld
* mods by	: P. Kavvathas, B. Rabenort, N. Koetsveld
* CPU      : STM32F4
* IDE      : Atollic TrueSTUDIO
* Module   : CMSIS_BOOT, M4_CMSIS_CORE
* Function : Error code output, with boundary check
*/

#include "include.h"
#include "error.h"
#include "stm32_ub_vga_screen.h"

/**
 * Error pointer that returns a error code to the UART
 */
void pError(uint8_t errnum)
{
	UART_puts("\nValue of errno: ");
	UART_putint(errnum);

	switch(errnum) {
		case 1  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

	   case 2  :
		   UART_puts("\nThis color does not exist!\n");
		   break;

		case 3  :
			UART_puts("\nThis function does not exist!\n");
			break;

		case 4  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 5 	:
			UART_puts("\nPlease check value's to prevent this overflow!\n");
			break;

		case 50	:
			UART_puts("\nPlease be aware of large time delay.");
			break;

		default:
			UART_puts("\nPlease note that this error value has no definition.\n");
			break;
	};
}

/** Out of bound function
 * Checks if coordinates are off screen
 */
uint8_t bound(uint16_t x, uint16_t y, uint8_t *perr) {
	if (x < 0 || y < 0 || x > VGA_DISPLAY_X || y > VGA_DISPLAY_Y) {
		*perr = ERR_OUT_OF_BOUND;
		pError(*perr);
		return 1;
	} else {
		return 0;
	}
}
