/**
  *
  *@file    	main.c
  * @author 	UB, J.F. van der Bent, P. Kavvathas, B. Rabenort, N. Koetsveld
  * @version	V0.51
  * @date   	24-Mei-2018
  * @brief  	Main
  *
  * \n CPU      : STM32F4\n
 	IDE      : Atollic TrueSTUDIO\n
	Module   : CMSIS_BOOT, M4_CMSIS_CORE\n
	Function : VGA_core DMA LIB 320x240, 8bit color\n
  *
  */

#include "main.h"
#include "include.h"
#include "Doxygen.c"
//#include "stm32_ub_vga_screen.h"
//#include <math.h>
//#include "draw_API.h"
//#include "error.h"

/**
 * Version number for displaying
 */
char *version = "API v0.51";

/**
 * Int for error codes
 */
uint8_t error;

/** @brief	Main code
 *
 * Initialization and main loop for getting code from the UART
 */
int main(void)
{
//	  uint32_t n;
	uint8_t error;

	// Inits
	SystemInit(); 			// System speed to 168MHz
	LCD_init();
	UART_init();
	LED_init();
	DELAY_init();
	UB_VGA_Screen_Init(); 	// Init VGA-Screen
	START_UP(); 			// Startup screen, LCD output, LED animation
		
	while(1)
	{
		char **arguments = UART_tokens();
		UART_control(arguments, &error);

		/** ALWAYS clear AFTER you are done with your arguments to prevent memory leaks! */
		UART_tokens_free(arguments);
	}
}

