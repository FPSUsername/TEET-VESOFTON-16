// Debugging
//#define DEBUG

// Standard
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// OS
#include "misc.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32_ub_vga_screen.h"

// Libs
#include "stddef.h"
#include "uart.h"
#include "delay.h"
#include "lcd.h"
#include "leds.h"
#include "ui.h"
#include "draw_API.h"
#include "error.h"
