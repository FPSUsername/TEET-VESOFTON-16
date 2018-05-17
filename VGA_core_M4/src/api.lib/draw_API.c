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
#include "font.h"

int change_col(char color[16]){
	int col;
	if 		(strcmp(color, "wit") == 0) {
		col = VGA_COL_WHITE;
	}
	else if (strcmp(color, "grijs") == 0) {
		col = VGA_COL_GRAY;
	}
	else if (strcmp(color, "zwart") == 0) {
		col = VGA_COL_BLACK;
	}
	else if (strcmp(color, "bruin") == 0) {
		col = VGA_COL_BROWN;
	}
	else if (strcmp(color, "blauw") == 0) {
		col = VGA_COL_BLUE;
	}
	else if (strcmp(color, "lichtblauw") == 0) {
		col = VGA_COL_LIGHT_BLUE;
	}
	else if (strcmp(color, "groen") == 0) {
		col = VGA_COL_GREEN;
	}
	else if (strcmp(color, "lichtgroen") == 0) {
		col = VGA_COL_LIGHT_GREEN;
	}
	else if (strcmp(color, "rood") == 0) {
		col = VGA_COL_RED;
	}
	else if (strcmp(color, "lichtrood") == 0) {
		col = VGA_COL_LIGHT_RED;
	}
	else if (strcmp(color, "cyan") == 0) {
		col = VGA_COL_CYAN;
	}
	else if (strcmp(color, "lichtcyan") == 0) {
		col = VGA_COL_LIGHT_CYAN;
	}
	else if (strcmp(color, "magenta") == 0) {
		col = VGA_COL_MAGENTA;
	}
	else if (strcmp(color, "lichtmagenta") == 0) {
		col = VGA_COL_LIGHT_MAGENTA;
	}
	else if (strcmp(color, "geel") == 0) {
		col = VGA_COL_YELLOW;
	}
	else if (strcmp(color, "roze") == 0) {
		col = VGA_COL_PINK;
	}
	else if (strcmp(color, "paars") == 0) {
		col = VGA_COL_PURPLE;
	}
	else {
		col = VGA_COL_WHITE;
	}//enum

	return col;
}

uint8_t line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t thickness, char color[16])
{
	int col = change_col(color);
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

uint8_t arrow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t thickness, char color[16])
{
	int col = change_col(color);

	return 2;
};

uint8_t ellipse(uint8_t x1, uint8_t y1, uint8_t xradius, uint8_t yradius, char color[16])
{
	int col = change_col(color);


	return 3;
};

uint8_t ellipse_filled(uint8_t x1, uint8_t y1, uint8_t xradius, uint8_t yradius, char color[16])
{
	int col = change_col(color);

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

uint8_t rectangular(uint8_t x1, uint8_t y1, uint8_t xlength, uint8_t ylength, char color[16])//als er 6argumenten worden gegeven word de dikte meegerekend
{
	char col = change_col(color);

	int16_t i;
	for (i=x1; i<x1; i++) {
		UB_VGA_SetPixel(i + xlength, y1, col);
		UB_VGA_SetPixel(i + xlength, y1 + ylength - 1, col);
	}
	for (i=y1; i<y1; i++) {
		UB_VGA_SetPixel(x1, i + ylength, col);
		UB_VGA_SetPixel(x1 + xlength - 1, i + ylength, col);
	}

	return 5;
};

uint8_t rectangular_thick(uint8_t x1, uint8_t y1, uint8_t xlength, uint8_t ylength, uint8_t tx, uint8_t ty, char color[16])//als er 6argumenten worden gegeven word de dikte meegerekend
{
	char col = change_col(color);
    int16_t i, t;

	if (tx <= 0) tx = 1;
	if (ty <= 0) ty = 1;

	for (i=x1; i<x1; i++) {
		for (t=0; t<(ty); t++) {
			UB_VGA_SetPixel(i + xlength, y1 + t, col);
			UB_VGA_SetPixel(i + xlength, y1 + ylength - t, col);
		}
	}
	for (i=y1; i<y1; i++) {
		for (t=0; t<(tx); t++) {
			UB_VGA_SetPixel(x1 + t, i + ylength, col);
			UB_VGA_SetPixel(x1 + xlength - t, i + ylength, col);
		}
	}

	return 5;
};

uint8_t rectangular_filled(uint8_t x1, uint8_t y1, uint8_t xlength, uint8_t ylength, char color[16])//als er 6argumenten worden gegeven word de dikte meegerekend
{
	char col = change_col(color);

	int16_t i, j;
		for (i=x1; i<x1; i++) {
			for (j=y1; j<y1; j++) {
				UB_VGA_SetPixel(i + xlength, j + ylength, col);
		}
	}

	return 6;
};

uint8_t triangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, char color[16])
{
	int col = change_col(color);
	return 7;
};


uint8_t print_char(uint8_t x1, uint8_t y1, char str, char color[16], char font[16])
{
	int col = change_col(color);
	int16_t i, j;

	// Iterate through the 13 rows
	for (j=0; j<13;j++) {

		for (i =0; i<7; i++) {
			if ( ( font[str][j] & (1 << i ) ) != 0 )
				setpixel(i + x1, j + y1, col); // Set the pixels
		}
	}

	return 8;
};

uint8_t print_text(uint8_t x1, uint8_t y1, char str[255], char color[16], char font[16])
{
	char ch;
	int i, x, y = 0;

	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;

	while (ch[i] != '\0') {
		print_char(x1 + x, y1 + y, ch[i], col, font);
		if (x < 320 - 9)
			x += 9; // 9 collums, 2 pixels spacing
		else {
			x = 0; // cursor position;
			y += 15; // 13 rows, 2 pixels spacing
		}
		i++;
	}
	return 9;
};

uint8_t bitmap(uint8_t bitmap, uint8_t x1, uint8_t y1)
{
	int16_t x, y;
	int16_t k = 4096;
	int16_t size = sizeof(bitmaps[bitmap]) / sizeof(bitmaps[bitmap][0]); // Amount of pixels
	int16_t x_p, y_p = sqrt(size);

	for (x=x1; x<64 + x1; x++) { // x_p
		for (y=y1; y<64 + y1; y++) { // y_p
			if (bitmaps[bitmap][k] != 0) UB_VGA_SetPixel(x, y, bitmaps[bitmap][k]);
			k--;
		}
	}
	return 10;
};

uint8_t fill_screen(char color[16])
{
	int col = change_col(color);

	UB_VGA_FillScreen(col);
	return 11;
};
