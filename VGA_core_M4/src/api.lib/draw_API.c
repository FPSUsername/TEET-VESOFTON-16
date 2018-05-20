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
#include "arial8x8_black.h"
#include "arial8x8_italic.h"
#include "arial8x8_regular.h"

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
	size_t len;
	UART_puts("\nLine\nX1\tY1\tX2\tY2\tThick\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(x2) + sizeof(y2) + sizeof(thickness) + strlen(color) + 1;
	UART_printf(len + 6, "\n%d\t%d\t%d\t%d\t%d\t%s", x1, y1, x2, y2, thickness, color);
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
	#ifdef DEBUG
	size_t len;
	UART_puts("\nArrow\nX1\tY1\tX2\tY2\tThick\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(x2) + sizeof(y2) + sizeof(thickness) + strlen(color) + 1;
	UART_printf(len + 6, "\n%d\t%d\t%d\t%d\t%d\t%s", x1, y1, x2, y2, thickness, color);
	#endif
//	uint8_t col = change_col(color);

	return 2;
};

uint8_t ellipse(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16])
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nEllipse\nX1\tY1\txRadius\tyRadius\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xRadius) + sizeof(yRadius) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xRadius, yRadius, color);
	#endif

//	uint8_t col = change_col(color);

	return 3;
};

uint8_t ellipse_filled(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16])
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nEllipse_filled\nX1\tY1\txRadius\tyRadius\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xRadius) + sizeof(yRadius) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xRadius, yRadius, color);
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
	size_t len;
	UART_puts("\nRectangular\nX1\tY1\txLength\tyLength\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xlength) + sizeof(ylength) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xlength, ylength, color);
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
	size_t len;
	UART_puts("\nRectangular_thick\nX1\tY1\txLength\tyLength\tX_thick\tY_thick\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xlength) + sizeof(ylength) + sizeof(tx) + sizeof(ty) + strlen(color) + 1;
	UART_printf(len + 7, "\n%d\t%d\t%d\t%d\t%d\t%d\t%s", x1, y1, xlength, ylength, tx, ty, color);
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
	size_t len;
	UART_puts("\nRectangular_filled\nX1\tY1\txLength\tyLength\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xlength) + sizeof(ylength) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xlength, ylength, color);
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
	size_t len;
	UART_puts("\nPrint_char\nX1\tY1\tChar\tColor\tFont");
	len = sizeof(x1) + sizeof(y1) + 1 + strlen(color) + strlen(font) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%c\t%s\t%s", x1, y1, chr, color, font);
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
			else if (strcmp(font, "cursief") == 0)
				set = arial8x8_italic[chr][x] & 1 << y;
			else if (strcmp(font, "vet") == 0)
				set = arial8x8_black[chr][x] & 1 << y;
			else // Normal font
				set = arial8x8_regular[chr][x] & 1 << y;
			if (set)
				UB_VGA_SetPixel(x1 + y, y1 + x, col);
		}
	}

	return 8;
};

uint8_t print_text(int16_t x1, int16_t y1, char str[], char color[16], char font[16])
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nPrint_text\nX1\tY1\tString");
	len = sizeof(x1) + sizeof(y1) + strlen(str) + 1;
	UART_printf(len + 3, "\n%d\t%d\t%s", x1, y1, str);
	UART_puts("\nColor\tFont");
	len = strlen(color) + strlen(font) +1;
	UART_printf(len + 2, "\n%s\t%s", color, font);
	#endif

	uint8_t margin = 8; // Display margin
	uint16_t x = 0;
	uint16_t y = 0;
	char *p = str;
	unsigned char current_char;

	if (x1 < margin) x1 = margin;
	if (y1 < margin) y1 = margin;

	// Offscreen
	if (x1 > (VGA_DISPLAY_X - 8 - margin)) return 91;
	if (y1 > (VGA_DISPLAY_Y - 8 - margin)) return 92;

	while (*p) {
		current_char = *p++; // Take current char and increment it for the next char
		print_char(x1 + x, y1 + y, current_char, color, font);

		// Next character and next line
		if ((x + x1) < (VGA_DISPLAY_X - 8 - margin)) // 8 because the font size is 8 wide
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
