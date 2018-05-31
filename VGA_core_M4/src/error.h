/**
 *
  *@file    	error.h
  * @author 	P. Kavvathas, B. Rabenort, N. Koetsveld
  * @version	V0.1
  * @date   	24-Mei-2018
  * @brief  	Error code define
*/

/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
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
