#include "stdint.h"

char ** UART_tokens();
void UART_tokens_clear(char **array);
void UART_control(char **array, uint8_t *perr);
void START_UP(void);
