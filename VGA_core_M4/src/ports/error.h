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

/*! \mainpage Drawing Shapes
 *
 * This project helps user to draw shapes.
 * Currently two types of shapes can be drawn:
 * - \subpage drawingRectanglePage "How to draw rectangle?"
 *
 * - \subpage drawingCirclePage "How to draw circle?"
 *
 */

/*! \page drawingRectanglePage How to draw rectangle?
 *
 * Lorem ipsum dolor sit amet
 *
 */

/*! \page drawingCirclePage How to draw circle?
 *
 * This page is about how to draw a circle.
 * Following sections describe circle:
 * - \ref groupCircleDefinition "Definition of Circle"
 * - \ref groupCircleClass "Circle Class"
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
