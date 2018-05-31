<<<<<<< HEAD
/**
 *
  *@file    	error.h
  * @author 	P. Kavvathas, B. Rabenort, N. Koetsveld
  * @version	V0.1
  * @date   	24-Mei-2018
  * @brief  	Error code define
*/

=======
>>>>>>> master
/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
<<<<<<< HEAD
#include "stdint.h"

/**Error code intended for the developers*/
#define ERR_UNKNOWN                     0u
/**Error code that the coordinates are out boundaries*/
#define ERR_OUT_OF_BOUND				1u
/**Error code for undefined/unknown color*/
#define ERR_COLOR						2u
/**Error code that the function doesn't exist*/
#define ERR_INPUT_INVALID				3u
/**Error code for the size of object*/
#define ERR_SIZE						4u
/**Error code for to large value for data type*/
#define ERR_OVERFLOW					5u

/*
*********************************************************************************************************
*                                             WARNING CODES
*********************************************************************************************************
*/
/**Warning that the asked time delay is unnecessarily large*/
#define WAR_TIMEDELAY					50u

void pError(uint8_t errnum);
uint8_t bound(uint16_t x, uint16_t y, uint8_t *perr);
=======
#define OS_ERR_NONE                     0u

#define RECT_ERR_OUTOFBOUND				1u
#define RECT_ERR_COLOR					2u
#define RECT_ERR_INPUTINVALID			3u
#define RECT_ERR_SIZE					4u

#define ELL_ERR_OUT_OF_BOUND			11u
#define ELL_ERR_COLOR					12u
#define ELL_ERR_INPUTINVALID			13u

#define LINE_ERR_OUTOFBOUND				21u
#define LINE_ERR_COLOR					22u
#define LINE_ERR_INPUTINVALID			23u
#define LINE_ERR_SIZE					24u

#define BIT_ERR_OUT_OF_BOUND			31u

/*
OSMutexPend(MutexHandle, WAIT_FOREVER, &error);
if(error)
{
   	UART_puts("\n\r0:mutexpend error=");
 	UART_putint(error);
 	UART_puts("\n\r");
}
*/



uint8_t STRERR(uint8_t errnum)
{
	switch(errnum) {
		case 1  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

	   case 2  :
		   UART_puts("\nPlease stay within screen boundaries!\n");
		   break;

		case 3  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 4  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 5  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 31:
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;
		default:
			UART_puts("/nPlease note that this error value has no definition");
};
>>>>>>> master
