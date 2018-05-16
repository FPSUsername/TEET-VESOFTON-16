//--------------------------------------------------------------
// color designation
// 8bit color (R3G3B2)
// Red   (3bit) -> Bit7-Bit5
// Green (3bit) -> Bit4-Bit2
// Blue  (2bit) -> Bit1-Bit0
//--------------------------------------------------------------
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

typedef unsigned char uint8_t;

uint8_t line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t thickness,char color[16]);
//uint8_t arrow(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t thickness,char color[16]);
//uint8_t ellips(uint8_t x1,uint8_t y1,uint8_t xradius,uint8_t yradius,char color[16]);
//uint8_t rectangular(uint8_t x1,uint8_t y1,uint8_t xlength,uint8_t ylength,char color[16]); //als er 6argumenten worden gegeven word de dikte meegerekend
//uint8_t triangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t x3,uint8_t y3,char color[16]);
//uint8_t text(uint8_t x1,uint8_t y1,char str[255],char color[16],char font[16]);
//uint8_t bitmap(uint8_t bitmap,uint8_t x1,uint8_t y1);
//uint8_t delay_ms(uint16_t time);
uint8_t fill_screen(char color[16]);
