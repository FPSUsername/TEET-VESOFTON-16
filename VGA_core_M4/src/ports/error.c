#include "include.h"
#include "error.h"
#include "stm32_ub_vga_screen.h"

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
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 4  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		default:
			UART_puts("\nPlease note that this error value has no definition.\n");
			break;
	};
}

uint8_t bound(uint16_t x, uint16_t y, uint8_t *perr) {
	if (x < 0 || y < 0 || x > VGA_DISPLAY_X || y > VGA_DISPLAY_Y) {
		*perr = ERR_OUT_OF_BOUND;
		pError(*perr);
		return 1;
	} else {
		return 0;
	}
}
