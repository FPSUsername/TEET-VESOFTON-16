/*
 * draw.c
 *
 *  Created on: 3 mei 2018
 *      Author: Bas
 */

struct draw
{
	uint8 line(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 thickness,char color[16])
	{

	};
	uint8 arrow(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 thickness,char color[16])
	{

	};
	uint8 ellips(uint8 x1,uint8 y1,uint8 xradius,uint8 yradius,char color[16])
	{

	};
	uint8 rectangular(uint8 x1,uint8 y1,uint8 xlength,uint8 ylength,char color[16])//als er 6argumenten worden gegeven word de dikte meegerekend
	{

	};
	uint8 triangle(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 x3,uint8 y3,char color[16])
	{

	};
	uint8 text(uint8 x1,uint8 y1,char str[255],char color[16],char font[16])
	{

	};
	uint8 bitmap(uint8 bitmap,uint8 x1,uint8 y1)
	{

	};
	uint8 delay_ms(uint16 time)
	{

	};
	uint8 fillscreen(char color[16])
	{

	};
};

