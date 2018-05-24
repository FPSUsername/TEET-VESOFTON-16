/*
 * draw.c
 *
 *  Created on: 3 mei 2018
 *      Author: Bas
 */

#include "include.h"
//#include <draw_API.h>
//#include "stm32_ub_vga_screen.h"
//#include "error.h"

// Bitmaps
#include "bitmap_1.h"

// Fonts
#include "font8x8_basic.h"
#include "font8x8_greek.h"
#include "arial8x8_black.h"
#include "arial8x8_italic.h"
#include "arial8x8_regular.h"
#include "verdana8x8_basic.h"

extern uint8_t error;
uint8_t err;

/* Change Col
 * This function "translates" the input string to the defined hex color values
 */
uint8_t change_col(char color[16], uint8_t *perr){
	uint8_t col;
	err = 0;
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
	else {
		col = VGA_COL_WHITE;
		*perr = ERR_COLOR;
		pError(*perr);
		err = 1;
	}
	return col;
};

/* Lijn
 * Function to plot a line
 */
uint8_t lijn(int16_t x1, int16_t y1, int16_t x2, int16_t y2, char color[16]){
	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

	int dx =  abs (x2 - x1), sx = x1 < x2 ? 1 :  - 1;
	int dy =  - abs (y2 - y1), sy = y1 < y2 ? 1 :  - 1;
	int err = dx + dy, e2; /* error value e_xy */

	while(1){  /* loop */
	  if(x1<=VGA_DISPLAY_X || y1<=VGA_DISPLAY_Y){
		  UB_VGA_SetPixel(x1, y1, col);
		  UB_VGA_SetPixel(x1, y1+1, col);
	  }
	  if (x1 == x2 && y1 == y2) break;
	  e2 = 2 * err;
	  if (e2 >= dy) { err += dy; x1 += sx; } /* e_xy + e_x > 0 */
	  if (e2 <= dx) { err += dx; y1 += sy; } /* e_xy + e_y < 0 */
	}
	return 0;
}

/* Line
 * Function to plot a line with thickness and color as a parameter
 */
uint8_t line(int16_t xi, int16_t yi, int16_t xii, int16_t yii, uint8_t thickness, char color[16], uint8_t *perr)
{

	#ifdef DEBUG
	size_t len;
	UART_puts("\nLine\nX1\tY1\tX2\tY2\tThick\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(x2) + sizeof(y2) + sizeof(thickness) + strlen(color) + 1;
	UART_printf(len + 6, "\n%d\t%d\t%d\t%d\t%d\t%s", x1, y1, x2, y2, thickness, color);
	#endif

	if(bound(xi, yi, &error) || bound(xii, yii, &error)); // Out of bound check
	//	return 1;

	int16_t x1,x2,y1,y2;
	x1 = xi;
	y1 = yi;
	x2 = xii;
	y2 = yii;
	float rc, x_rc, y_rc;
	float  x_r, y_r;

	x_r = x2-x1;
	y_r = y2-y1;
	x_rc = y_r *-1; //door onderstaande berekening ontstaat er een lijn die 90graden op de te tekenen lijn achterloopt
	y_rc = x_r;
	rc= sqrt((x_rc*x_rc)+(y_rc*y_rc));

	lijn(x1,y1,x2,y2,color);

	for (int i=1; i<= thickness; i++) {
		int xx= (i/rc)*x_rc+xi; // casten misschien?
		int yy= (i/rc)*y_rc+yi;
		int x02=  (xx-xi) + xii;
		int y02= (yy-yi)+ yii;
		lijn(xx,yy,x02,y02,color);
	}

	return 0;
};

/* Arrow
 * Function that plots an arrow, not implemented
 */
uint8_t arrow(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t thickness, char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nArrow\nX1\tY1\tX2\tY2\tThick\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(x2) + sizeof(y2) + sizeof(thickness) + strlen(color) + 1;
	UART_printf(len + 6, "\n%d\t%d\t%d\t%d\t%d\t%s", x1, y1, x2, y2, thickness, color);
	#endif
//	uint8_t col = change_col(color, &error);
//	if (err)
//		return 1;

	if(bound(x1, y1, &error) || bound(x2, y2, &error)) // Out of bound check
		return 1;

	return 0;
};

/* Ellipse
 * Function to plot an ellipse outline
 */
uint8_t ellipse(int16_t xc, int16_t yc, int16_t rx, int16_t ry, char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nEllipse\nX1\tY1\txRadius\tyRadius\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xRadius) + sizeof(yRadius) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xRadius, yRadius, color);
	#endif

	if(bound(xc, yc, &error)); // Out of bound check

	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

   int x, y, p;
   x=0;
   y=ry;
   p=(ry*ry)-(rx*rx*ry)+((rx*rx)/4);
   while((2*x*ry*ry)<(2*y*rx*rx))
   {
	   if(xc+x<=VGA_DISPLAY_X || yc-y<=VGA_DISPLAY_Y) UB_VGA_SetPixel(xc+x,yc-y,col);
	   if(xc-x<=VGA_DISPLAY_X || yc+y<=VGA_DISPLAY_Y) UB_VGA_SetPixel(xc-x,yc+y,col);
	   if(xc+x<=VGA_DISPLAY_X || yc+y<=VGA_DISPLAY_Y) UB_VGA_SetPixel(xc+x,yc+y,col);
	   if(xc-x<=VGA_DISPLAY_X || yc-y<=VGA_DISPLAY_Y) UB_VGA_SetPixel(xc-x,yc-y,col);

		if(p<0)
		{
	 x=x+1;
	 p=p+(2*ry*ry*x)+(ry*ry);
		}
		else
		{
	 x=x+1;
	 y=y-1;
	 p=p+(2*ry*ry*x+ry*ry)-(2*rx*rx*y);
		}
   }
   p=((float)x+0.5)*((float)x+0.5)*ry*ry+(y-1)*(y-1)*rx*rx-rx*rx*ry*ry;

		 while(y>=0)
   {
		if(xc+x<=VGA_DISPLAY_X || yc-y<=VGA_DISPLAY_Y)	 UB_VGA_SetPixel(xc+x,yc-y,col);
		if(xc-x<=VGA_DISPLAY_X || yc+y<=VGA_DISPLAY_Y)	 UB_VGA_SetPixel(xc-x,yc+y,col);
		if(xc+x<=VGA_DISPLAY_X || yc+y<=VGA_DISPLAY_Y)	 UB_VGA_SetPixel(xc+x,yc+y,col);
		if(xc-x<=VGA_DISPLAY_X || yc-y<=VGA_DISPLAY_Y)	 UB_VGA_SetPixel(xc-x,yc-y,col);

		if(p>0)
		{
			 y=y-1;
			 p=p-(2*rx*rx*y)+(rx*rx);

		}
		else
		{
			 y=y-1;
			 x=x+1;
			 p=p+(2*ry*ry*x)-(2*rx*rx*y)-(rx*rx);
		}
	 }

	return 0;
};

/* Ellipse Filled
 * Function to plot a filled ellipse
 */
uint8_t ellipse_filled(int16_t x1, int16_t y1, int16_t xradius, int16_t yradius, char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nEllipse_filled\nX1\tY1\txRadius\tyRadius\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xRadius) + sizeof(yRadius) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xRadius, yRadius, color);
	#endif

	if(bound(x1, y1, &error)); // Out of bound check


	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

	for(int y= -yradius; y<=yradius; y++) {
	    for(int x= -xradius; x<=xradius; x++) {
	        double dx = (double)x / (double)xradius;
	        double dy = (double)y / (double)yradius;
	        if(dx*dx + dy*dy <= 1)
	        	UB_VGA_SetPixel(x + x1, y + y1, col);
	    }
	}
	return 0;
};

/* Rectangular
 * Function to plot a rectangular
 */
uint8_t rectangular(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nRectangular\nX1\tY1\txLength\tyLength\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xlength) + sizeof(ylength) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xlength, ylength, color);
	#endif

	if(bound(x1, y1, &error)) // Out of bound check
		return 1;

	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

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

	return 0;
};

/* Rectangular Thick
 * Function to plot a rectangular with thickness as an extra parameter
 */
uint8_t rectangular_thick(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, uint8_t tx, uint8_t ty, char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nRectangular_thick\nX1\tY1\txLength\tyLength\tX_thick\tY_thick\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xlength) + sizeof(ylength) + sizeof(tx) + sizeof(ty) + strlen(color) + 1;
	UART_printf(len + 7, "\n%d\t%d\t%d\t%d\t%d\t%d\t%s", x1, y1, xlength, ylength, tx, ty, color);
	#endif

	if(bound(x1, y1, &error)) // Out of bound check
		return 1;

	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

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

	return 0;
};

/* Rectangular Filled
 * Function to plot a filled rectangular
 */
uint8_t rectangular_filled(uint16_t x1, uint16_t y1, uint16_t xlength, uint16_t ylength, char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nRectangular_filled\nX1\tY1\txLength\tyLength\tColor");
	len = sizeof(x1) + sizeof(y1) + sizeof(xlength) + sizeof(ylength) + strlen(color) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%d\t%d\t%s", x1, y1, xlength, ylength, color);
	#endif

	if(bound(x1, y1, &error)) // Out of bound check
		return 1;

	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

	// Out of screen
	if (x1 + xlength > VGA_DISPLAY_X)	xlength = -x1 - VGA_DISPLAY_X;
	if (y1 + ylength > VGA_DISPLAY_Y)	ylength = -y1 - VGA_DISPLAY_Y;

	int16_t x, y;
		for (x=x1; x<x1 + xlength; x++) {
			for (y=y1; y<y1 + ylength; y++) {
				UB_VGA_SetPixel(x, y, col);
		}
	}

	return 0;
};

/* Triangle
 * Function to plot a triangle by using three points on the screen
 */
uint8_t triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, char color[16])
{
	if(bound(x1, y1, &error) || bound(x2, y2, &error) || bound(x3, y3, &error)) // Out of bound check
		return 1;

	lijn(x1,y1,x2,y2,color);
	lijn(x2,y2,x3,y3,color);
	lijn(x3,y3,x1,y1,color);
	return 0;
};

/* Triangle Filled
 * Function to plot a filled triangle by using three points on the screen
 */
uint8_t triangle_filled(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, int16_t X3, int16_t Y3, char color[16])
{
	if(bound(X1, Y1, &error) || bound(X2, Y2, &error) || bound(X3, Y3, &error)); // Out of bound check
	//	return 1;

	int x01 = abs(X2-X1);
	int x02 = abs(X3-X2);
	int x03 = abs(X1-X3);
	int x1,y1,x2,y2,x3,y3;

	if(((x01<x02)&&(x02<x03)) || ((x01>x02)&&(x02<x03)) || X1==X2)
	{
		x1 = X2;
		y1 = Y2;
		x2 = X3;
		y2 = Y3;
		x3 = X1;
		y3 = Y1;
	}
	if(((x02<x01)&&(x01>x03)) || ((x01>x02)&&(x01<x03)) || X2==X3)
	{
		x1 = X1;
		y1 = Y1;
		x2 = X2;
		y2 = Y2;
		x3 = X3;
		y3 = Y3;
	}
	if(((x03<x01)&&(x03>x02)) || ((x03>x01)&&(x03<x02)) || X3==X1)
	{
		x1 = X3;
		y1 = Y3;
		x2 = X1;
		y2 = Y1;
		x3 = X2;
		y3 = Y2;
	}

	float x_r = x2-x1;
	float y_r = y2-y1;
	float rc = (y_r/x_r);
	if(x_r<0){
		for(int i=(x_r*10); i< 0; i++){

			float yy= ((i/10)*rc)+y1; // casten misschien?
			lijn(((i/10)+x1),yy,x3,y3,color);
		}
	}
	if(x_r>0){
		for(int i=0; i<(x_r*10); i++){
			float yy= ((i/10)*rc)+y1; // casten misschien?
			lijn(((i/10)+x1),yy,x3,y3,color);
		}
	}

	return 0;
};

/* Print Char
 * Function to print one character on the screen
 * Currently allows for these styles:
 * Greek (difficult to use since the characters are not equal to the characters of your keyboard)
 * Italic
 * Bold
 * Regular
 */
uint8_t print_char(int16_t x1, int16_t y1, uint8_t chr, char color[16], char font[16], uint8_t *perr)
{
	#ifdef DEBUG
	size_t len;
	UART_puts("\nPrint_char\nX1\tY1\tChar\tColor\tFont");
	len = sizeof(x1) + sizeof(y1) + 1 + strlen(color) + strlen(font) + 1;
	UART_printf(len + 5, "\n%d\t%d\t%c\t%s\t%s", x1, y1, chr, color, font);
	#endif
	uint8_t col = change_col(color, &error);
	if (err)
		return 1;
	uint8_t set;
	uint8_t size = 8; // font size (h and v)
	uint16_t x, x_p, y, y_p;

	if(bound(x1, y1, &error)) // Out of bound check
		return 1;

	for (x = 0; x < size; x++) { // Horizontal, x-- results into flipping
		for (y = 0; y < size; y++) { // Vertical
			if (strcmp(font, "greek") == 0) {
				set = font8x8_greek[chr][x] & 1 << y;
				x_p = x1 + y;
				y_p = y1 + x;
			}
			else if (strcmp(font, "cursief") == 0) {
				set = arial8x8_italic[chr][x] & 1 << y;
				x_p = x1 + x;
				y_p = y1 + y;
			}
			else if (strcmp(font, "vet") == 0) {
				set = arial8x8_black[chr][x] & 1 << y;
				x_p = x1 + x;
				y_p = y1 + y;
			}
			else { // Normal font
//				set = arial8x8_regular[chr][x] & 1 << y;
//				set = Verdana8x8[chr][x] & 1 << y;
				set = font8x8_basic[chr][x] & 1 << y;
				x_p = x1 + y;
				y_p = y1 + x;
			}
			if (set)
				UB_VGA_SetPixel(x_p, y_p, col);
		}
	}

	return 0;
};

/* Print Text
 * Function to print strings on the screen
 * Features:
 * Build in OUT_OF_BOUND error workaround (The error still exists in the same form, but you have to interpret that as a warning)
 * Automatic next line with left alignment (fills till the end of the screen)
 */
uint8_t print_text(int16_t x1, int16_t y1, char str[], char color[16], char font[16], uint8_t *perr)
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

	if(bound(x1, y1, &error)) // Out of bound check
		return 1;

	uint8_t margin = 8; // Display margin
	uint16_t x = 0;
	uint16_t y = 0;
	char *p = str;
	unsigned char current_char;

	// Offscreen
	if (x1 < margin) x1 = margin;
	else if (x1 > (VGA_DISPLAY_X - 8 - margin)) x1 = VGA_DISPLAY_X - 8 - margin;
	if (y1 < margin) y1 = margin;
	else if (y1 > (VGA_DISPLAY_Y - 8 - margin)) x1 = VGA_DISPLAY_Y - 8 - margin;

	while (*p) {
		current_char = *p++; // Take current char and increment it for the next char
		print_char(x1 + x, y1 + y, current_char, color, font, &error);

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
	return 0;
};

/* Bitmap
 * Function to print bitmaps
 * Only works with square bitmaps @256 colors
 */
uint8_t bitmap(uint8_t bitmap, int16_t x1, int16_t y1, uint8_t trans, uint8_t *perr)
{
	// This version can only print bitmaps that are squared
	#ifdef DEBUG
	UART_puts("\nBitmap\nNr\tX1\tY1\tTransparency\n");
	len = sizeof(x1) + sizeof(y1) + 1 + 1;
	UART_printf(len + 4, "\n%d\t%d\t%d\t%d", bitmap, x1, y1, trans);
	#endif

	if(bound(x1, y1, &error)) // Out of bound check
		return 1;

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
	return 0;
};

/* Delay
 * Freeze the system for XXXX time in milliseconds
 */
uint8_t DELAY(uint16_t time, uint8_t *perr)
{
	#ifdef DEBUG
	UART_puts("\nDelay\nMilliseconds: ");
	UART_putint(time);
	UART_puts("\n");
	#endif

	DELAY_ms(time);
	return 0;
};

/* Fillscreen
 * Function to fill the screen with one color
 */
uint8_t fill_screen(char color[16], uint8_t *perr)
{
	#ifdef DEBUG
	UART_puts("\nFill_screen\nColor: ");
	UART_puts(color);
	UART_puts("\n");
	#endif

	uint8_t col = change_col(color, &error);
	if (err)
		return 1;

	UB_VGA_FillScreen(col);
	return 0;
};
