/*
 * draw.c
 *
 *  Created on: 3 mei 2018
 *      Author: Bas
 */

#include <draw_API.h>
#include "stm32_ub_vga_screen.h"
#include "include.h"

uint8_t line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t thickness,char color[16])
{
	UART_puts("line");

//	unsigned char x, y;
//	for (x = x1; x < x2; x++){
//		for (y = y1; y < y2; y++){
//			UB_VGA_SetPixel(x,y,10);
//		}
//	}
	return 1;
};
uint8_t arrow(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t thickness,char color[16])
{
	UART_puts("pijl");
	return 2;
};
uint8_t ellips(uint8_t x1,uint8_t y1,uint8_t xradius,uint8_t yradius,char color[16])
{
	UART_puts("elips");
	return 3;
};
uint8_t rectangular(uint8_t x1,uint8_t y1,uint8_t xlength,uint8_t ylength,char color[16])//als er 6argumenten worden gegeven word de dikte meegerekend
{
	UART_puts("rechthoek");
	unsigned char x, y;
	for (x = x1; x < x1 + xlength; x++){
		for (y = y1; y < y1 + ylength; y++){
			UB_VGA_SetPixel(x,y,color);
		}
	}
	return 4;
};
uint8_t triangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t x3,uint8_t y3,char color[16])
{
	UART_puts("driehoek");
	return 5;
};
uint8_t text(uint8_t x1,uint8_t y1,char str[255],char color[16],char font[16])
{
	UART_puts("tekst");
	return 6;
};
uint8_t bitmap(uint8_t bitmap,uint8_t x1,uint8_t y1)
{
	UART_puts("bitmap");
	return 7;
};
uint8_t delay_ms(uint16_t time)
{
	UART_puts("wait");
	return 8;
};
uint8_t fill_screen(char color[16])
{
	UART_puts(color);
	UB_VGA_FillScreen(color);
	return 9;
};


void change_col(char color[16]){
	if (strcmp(color, "wit") == 0)			color = VGA_COL_WHITE;
	else if (strcmp(color, "grijs") == 0)	color = VGA_COL_GRAY;
	else if (strcmp(color, "zwart") == 0)	color = VGA_COL_BLACK;
	else if (strcmp(color, "bruin") == 0)	color = VGA_COL_BROWN;

}



