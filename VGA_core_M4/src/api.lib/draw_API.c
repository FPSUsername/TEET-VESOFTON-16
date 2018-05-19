/*
 * draw.c
 *
 *  Created on: 3 mei 2018
 *      Author: Bas
 */

#include <draw_API.h>
#include "stm32_ub_vga_screen.h"
#include "include.h"
#include "bitmap_1.h"
#include "font8x8_basic.h"
#include "font8x8_greek.h"

uint8_t change_col(char color[16]){
	uint8_t col;
	if 		(strcmp(color, "wit") == 0) 			col = VGA_COL_WHITE;
	else if (strcmp(color, "grijs") == 0)			col = VGA_COL_GRAY;
	else if (strcmp(color, "zwart") == 0)			col = VGA_COL_BLACK;
	else if (strcmp(color, "bruin") == 0)			col = VGA_COL_BROWN;
	else if (strcmp(color, "blauw") == 0) 			col = VGA_COL_BLUE;
	else if (strcmp(color, "lichtblauw") == 0)		col = VGA_COL_LIGHT_BLUE;
	else if (strcmp(color, "groen") == 0)			col = VGA_COL_GREEN;
	else if (strcmp(color, "lichtgroen") == 0)		col = VGA_COL_LIGHT_GREEN;
	else if (strcmp(color, "rood") == 0)			col = VGA_COL_RED;
	else if (strcmp(color, "lichtrood") == 0)		col = VGA_COL_LIGHT_RED;
	else if (strcmp(color, "cyaan") == 0)			col = VGA_COL_CYAN;
	else if (strcmp(color, "lichtcyan") == 0)		col = VGA_COL_LIGHT_CYAN;
	else if (strcmp(color, "magenta") == 0)			col = VGA_COL_MAGENTA;
	else if (strcmp(color, "lichtmagenta") == 0)	col = VGA_COL_LIGHT_MAGENTA;
	else if (strcmp(color, "geel") == 0)			col = VGA_COL_YELLOW;
	else if (strcmp(color, "roze") == 0)			col = VGA_COL_PINK;
	else if (strcmp(color, "paars") == 0)			col = VGA_COL_PURPLE;
	else 											col = VGA_COL_WHITE; // Error?
	//enum

	return col;
};

uint8_t line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t thickness, char color[16])
{
	#ifdef DEBUG
	UART_puts("\nLine\nX1\tY1\tX2\tY2\tThick\tColor\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(x2);
	UART_puts("\t");
	UART_putint(y2);
	UART_puts("\t");
	UART_putint(thickness);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\n");
	#endif

	uint8_t col = change_col(color);
	int dx =  abs (x2 - x1), sx = x1 < x2 ? 1 : -1;
	int dy =  ((-1) * abs (y2 - y1)), sy = y1 < y2 ? 1 : -1;
	UART_puts("DX: ");
	UART_putint(dx);
	UART_puts("\nDY: ");
	UART_putint(dy);
	int err = dx + dy, e2; /* error value e_xy */

	float rc, x_rc, y_rc;
	int x_thick1, y_thick1, x_thick2, y_thick2, dikke, x_dx, y_dy;
	x_dx = x2-x1;
	y_dy = y2-y1;

	x_rc = x2-x1;
	y_rc = y2-y1;
	x_rc = y_rc *-1; //door onderstaande berekening ontstaat er een lijn die 90graden op de te tekenen lijn achterloopt
	y_rc = x_rc;
	rc= sqrt((x_rc*x_rc)+(y_rc*y_rc));
	x_thick1= (rc/thickness)*x_rc; // casten misschien?
	y_thick1= (rc/thickness)*y_rc;
	x_thick2= x_thick1+x_dx;
	y_thick2= y_thick1+y_dy;
	dikke= 0;
	while(1){  /* loop */
		UB_VGA_SetPixel(x1,y1,col);
	  if (x1 == x2 && y1 == y2) break;
	  e2 = 2 * err;
	  if (e2 >= dy) { err += dy; x1 += sx; } /* e_xy+e_x > 0 */
	  if (e2 <= dx) { err += dx; y1 += sy; } /* e_xy+e_y < 0 */
	}
	while(1){
		UB_VGA_SetPixel(x_thick1,y_thick1,col);
		  e2 = 2 * err;
		  if (e2 >= dy) { err += dy; x_thick1 += sx; } /* e_xy+e_x > 0 */
		  if (e2 <= dx) { err += dx; y_thick1 += sy; } /* e_xy+e_y < 0 */

		if (x_thick1 == x_thick2 && y_thick1 == y_thick2){
			dikke++;
			x_thick1= (rc/dikke)*x_rc; // casten misschien?
			y_thick1= (rc/dikke)*y_rc;
			x_thick2= x_thick1+dx;
			y_thick2= y_thick1+dy;
			if(dikke==thickness)break;
		}

	}
//	int dx =  abs (x2 - x1), sx = x1 < x2 ? 1 :  - 1;
//	int dy =  - abs (y2 - y1), sy = y1 < y2 ? 1 :  - 1;
//	int err = dx + dy, e2; /* error value e_xy */
//
//	while(1){  /* loop */
//		UB_VGA_SetPixel(x1, y1, col);
//	  if (x1 == x2 && y1 == y2) break;
//	  e2 = 2 * err;
//	  if (e2 >= dy) { err += dy; x1 += sx; } /* e_xy + e_x > 0 */
//	  if (e2 <= dx) { err += dx; y1 += sy; } /* e_xy + e_y < 0 */
//	}
	return 1;
};

uint8_t arrow(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t thickness, char color[16])
{
//	uint8_t col = change_col(color);

	return 2;
};

uint8_t ellipse(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16])
{
	#ifdef DEBUG
	UART_puts("\nEllipse\nX1\tY1\txRadius\tyRadius\tColor\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(xradius);
	UART_puts("\t");
	UART_putint(yradius);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\n");
	#endif

//	uint8_t col = change_col(color);

	return 3;
};

uint8_t ellipse_filled(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16])
{
	#ifdef DEBUG
	UART_puts("\nEllipse_filled\nX1\tY1\txRadius\tyRadius\tColor\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(xradius);
	UART_puts("\t");
	UART_putint(yradius);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\n");
	#endif

	uint8_t col = change_col(color);

	for(int y= -yradius; y<=yradius; y++) {
	    for(int x= -xradius; x<=xradius; x++) {
	        double dx = (double)x / (double)xradius;
	        double dy = (double)y / (double)yradius;
	        if(dx*dx + dy*dy <= 1)
	        	UB_VGA_SetPixel(x + x1, y + y1, col);
	    }
	}
	return 4;
};

uint8_t rectangular(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, char color[16])
{
	#ifdef DEBUG
	UART_puts("\nRectangular\nX1\tY1\txLength\tyLength\tColor\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(xlength);
	UART_puts("\t");
	UART_putint(ylength);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\n");
	#endif

	uint8_t col = change_col(color);
	uint16_t i;

	// Out of screen
	if (x1 + xlength > VGA_DISPLAY_X)	xlength = -x1 - VGA_DISPLAY_X;
	if (y1 + ylength > VGA_DISPLAY_Y)	ylength = -y1 - VGA_DISPLAY_Y;

	for (i=x1; i<x1 + xlength; i++) {
		UB_VGA_SetPixel(i, y1, col);
		UB_VGA_SetPixel(i , y1 + ylength - 1, col);
	}
	for (i=y1; i<y1 + ylength; i++) {
		UB_VGA_SetPixel(x1, i, col);
		UB_VGA_SetPixel(x1 + xlength - 1, i, col);
	}

	return 5;
};

uint8_t rectangular_thick(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, uint8_t tx, uint8_t ty, char color[16])
{
	#ifdef DEBUG
	UART_puts("\nRectangular_thick\nX1\tY1\txLength\tyLength\tX_thick\tY_thick\tColor\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(xlength);
	UART_puts("\t");
	UART_putint(ylength);
	UART_puts("\t");
	UART_puts(tx);
	UART_puts("\t");
	UART_puts(ty);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\n");
	#endif

	uint8_t col = change_col(color);
    uint16_t i, t;

	// Out of screen
	if (x1 + xlength > VGA_DISPLAY_X)	xlength = -x1 - VGA_DISPLAY_X;
	if (y1 + ylength > VGA_DISPLAY_Y)	ylength = -y1 - VGA_DISPLAY_Y;

	if (tx == 0) tx = 1;
	if (ty == 0) ty = 1;

	for (i=x1; i<x1 + xlength; i++) {
		for (t=0; t<(ty); t++) {
			UB_VGA_SetPixel(i, y1 + t, col);
			UB_VGA_SetPixel(i , y1 + ylength - t, col);
		}
	}
	for (i=y1; i<y1 + ylength; i++) {
		for (t=0; t<(tx); t++) {
			UB_VGA_SetPixel(x1 + t, i, col);
			UB_VGA_SetPixel(x1 + xlength - t, i, col);
		}
	}

	return 5;
};

uint8_t rectangular_filled(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, char color[16])
{
	#ifdef DEBUG
	UART_puts("\nRectangular_filled\nX1\tY1\txLength\tyLength\tColor\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(xlength);
	UART_puts("\t");
	UART_putint(ylength);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\n");
	#endif
	uint8_t col = change_col(color);

	// Out of screen
	if (x1 + xlength > VGA_DISPLAY_X)	xlength = -x1 - VGA_DISPLAY_X;
	if (y1 + ylength > VGA_DISPLAY_Y)	ylength = -y1 - VGA_DISPLAY_Y;

	int16_t x, y;
		for (x=x1; x<x1 + xlength; x++) {
			for (y=y1; y<y1 + ylength; y++) {
				UB_VGA_SetPixel(x, y, col);
		}
	}

	return 6;
};

uint8_t triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, char color[16])
{
//	int8_t col = change_col(color);

	return 7;
};

uint8_t print_char(int16_t x1, int16_t y1, uint8_t chr, char color[16], char font[16])
{
	#ifdef DEBUG
	UART_puts("\nPrint_char\nX1\tY1\tChar\tColor\tFont\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putchar(chr);
	UART_puts("\t");
	UART_puts(color);
	UART_puts("\t");
	UART_puts(font);
	UART_puts("\n");
	#endif
	uint8_t col = change_col(color);
	uint8_t set;
	uint8_t size = 8; // font size (h and v)
	uint16_t x, y;

	// Offscreen
	if (x1 < 0 || x1 > (VGA_DISPLAY_X - size)) return 81;
	if (y1 < 0 || y1 > (VGA_DISPLAY_Y - size)) return 82;
	y = 0;

	for (x = 0; x < size; x++) { // Horizontal, x-- results into flipping
		for (y = 0; y < size; y++) { // Vertical
			if (strcmp(font, "greek") == 0)
				set = font8x8_greek[chr][x] & 1 << y;
			else
				set = font8x8_basic[chr][x] & 1 << y;
			if (set)
				UB_VGA_SetPixel(x1 + y, y1 + x, col);
		}
	}

	return 8;
};

uint8_t print_text(int16_t x1, int16_t y1, char str[], char color[16], char font[16])
{
	#ifdef DEBUG
	UART_puts("\nPrint_text\nX1\tY1\tString\n");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_puts(str);
	UART_puts("\nColor\tFont\n");
	UART_puts(color);
	UART_puts("\t");
	UART_puts(font);
	UART_puts("\n");
	#endif

	uint8_t margin = 8;
	uint16_t x = 0;
	uint16_t y = 0;
	size_t len = strlen(str);

	if (x1 < margin) x1 = margin;
	if (y1 < margin) y1 = margin;

	// Offscreen
	if (x1 > (VGA_DISPLAY_X - 8 - margin)) return 91;
	if (y1 > (VGA_DISPLAY_Y - 8 - margin)) return 92;

	for(int i = 0; i < len; i++) {
		print_char(x1 + x, y1 + y, str[i], color, font);
		if ((x + x1) < (VGA_DISPLAY_X - 8 - margin))
			x += 8; // No spacing needed
		else {
			x = 0; // cursor position;
			if ((y + y1) < (VGA_DISPLAY_Y - 8 - margin))
				y += 9; // 8 rows, 1 pixel spacing
			else
				y = 0; // Error, off screen!
		}
	}
	return 9;
};

uint8_t bitmap(uint8_t bitmap, int16_t x1, int16_t y1, uint8_t trans)
{
	#ifdef DEBUG
	UART_puts("\nBitmap\nNr\tX1\tY1\tTransparency\n");
	UART_putint(bitmap);
	UART_puts("\t");
	UART_putint(x1);
	UART_puts("\t");
	UART_putint(y1);
	UART_puts("\t");
	UART_putint(trans);
	UART_puts("\n");
	#endif
	// This version can only print bitmaps that are squared
	uint16_t x, y;
	uint16_t size = sizeof(bitmaps[bitmap]) / sizeof(bitmaps[bitmap][0]); // Amount of pixels
	uint16_t x_p = sqrt(size); // Amount of pixels on the x-axis
	uint16_t y_p = x_p; // Amount of pixels on the y-axis

	for (x = 0; x < x_p; x++) {
		for (y = 0; y < y_p; y++) {
			if (trans == 1) {
				if (bitmaps[bitmap][size] != 0) // 0 == 0x00, black screen
					UB_VGA_SetPixel(x1 + y_p - y, y1 + x_p - x, bitmaps[bitmap][size]);
			}
			else
				UB_VGA_SetPixel(x1 + y_p - y, y1 + x_p - x, bitmaps[bitmap][size]);
			size--;
		}
	}

	return 10;
};

uint8_t DELAY(uint16_t time)
{
	#ifdef DEBUG
	UART_puts("\nDelay\nMilliseconds: ");
	UART_putint(time);
	UART_puts("\n");
	#endif

	DELAY_ms(time);
	return 11;
};

uint8_t fill_screen(char color[16])
{
	#ifdef DEBUG
	UART_puts("\nFill_screen\nColor: ");
	UART_puts(color);
	UART_puts("\n");
	#endif

	uint8_t col = change_col(color);

	UB_VGA_FillScreen(col);
	return 12;
};
