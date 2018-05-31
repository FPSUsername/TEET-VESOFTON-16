/**
  *
  *@file    	draw_API.h
  * @author 	P. Kavvathas, B. Rabenort, N. Koetsveld
  * @version	V0.1
  * @date   	1-Mei-2018
  * @brief  	Color define
  *
  * \n color designation
  * 8bit color (R3G3B2)
  * Red   (3bit) -> Bit7-Bit5
  * Green (3bit) -> Bit4-Bit2
  * Blue  (2bit) -> Bit1-Bit0
*/

#include "stdint.h"

#define  VGA_COL_WHITE          0xFF
#define  VGA_COL_GRAY			0xBF
#define  VGA_COL_BLACK          0x00
#define  VGA_COL_BROWN			0xAD

#define  VGA_COL_BLUE           0x03
#define  VGA_COL_LIGHT_BLUE		0x6F

#define  VGA_COL_GREEN          0x1C
#define  VGA_COL_LIGHT_GREEN	0x9E

#define  VGA_COL_RED            0xE0
#define  VGA_COL_LIGHT_RED		0xE9

#define  VGA_COL_CYAN           0x1F
#define  VGA_COL_LIGHT_CYAN		0xBF

#define  VGA_COL_MAGENTA        0xE3
#define  VGA_COL_LIGHT_MAGENTA	0xF7

#define  VGA_COL_YELLOW         0xFC
#define  VGA_COL_PINK			0xEF
#define  VGA_COL_PURPLE			0x82

uint8_t change_col(char color[16], uint8_t *perr);
uint8_t lijn(int16_t x1, int16_t y1, int16_t x2, int16_t y2, char color[16]);
uint8_t line(int16_t xi, int16_t yi, int16_t xii, int16_t yii, uint8_t thickness, char color[16], uint8_t *perr);
uint8_t arrow(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t thickness, char color[16], uint8_t *perr);
uint8_t ellipse(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16], uint8_t *perr);
uint8_t ellipse_filled(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16], uint8_t *perr);
uint8_t rectangular(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, char color[16], uint8_t *perr);
uint8_t rectangular_thick(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, uint8_t tx, uint8_t ty, char color[16], uint8_t *perr);
uint8_t rectangular_filled(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, char color[16], uint8_t *perr);
uint8_t triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, char color[16]);
uint8_t triangle_filled(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, char color[16]);
uint8_t print_char(int16_t x1, int16_t y1, uint8_t chr, char color[16], char font[16], uint8_t *perr);
uint8_t print_text(int16_t x1, int16_t y1, char str[], char color[16], char font[16], uint8_t *perr);
uint8_t bitmap(uint8_t bitmap, int16_t x1, int16_t y1, uint8_t trans, uint8_t *perr);
uint8_t DELAY(uint16_t time, uint8_t *perr);
uint8_t fill_screen(char color[16], uint8_t *perr);
