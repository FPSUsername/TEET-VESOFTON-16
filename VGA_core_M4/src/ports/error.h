//--------------------------------------------------------------
// File     : error.h
// Datum    : 24.05.2018
// Version  : 0.1
// Author   : N. Koetsveld
// mods by	: P. Kavvathas, B. Rabenort, N. Koetsveld
// CPU      : STM32F4
// IDE      : Atollic TrueSTUDIO
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : Error codes,
//--------------------------------------------------------------

/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
#include "stdint.h"

#define ERR_UNKNOWN                     0u
#define ERR_OUT_OF_BOUND				1u
#define ERR_COLOR						2u
#define ERR_INPUT_INVALID				3u
#define ERR_SIZE						4u
#define ERR_OVERFLOW					5u

/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
#define WAR_TIMEDELAY					50u


void pError(uint8_t errnum);
uint8_t bound(uint16_t x, uint16_t y, uint8_t *perr);
