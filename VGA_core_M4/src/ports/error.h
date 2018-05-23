/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
#define OS_ERR_NONE                     0u

#define ERR_OUT_OF_BOUND				1u
#define ERR_COLOR						2u
#define ERR_INPUT_INVALID				3u
#define ERR_SIZE						4u

#include "stdint.h"

/*
OSMutexPend(MutexHandle, WAIT_FOREVER, &error);
if(error)
{
   	UART_puts("\n\r0:mutexpend error=");
 	UART_putint(error);
 	UART_puts("\n\r");
}
*/
void pError(uint8_t errnum);
uint8_t bound(uint16_t x, uint16_t y, uint8_t *perr);
