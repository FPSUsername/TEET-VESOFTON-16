/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
#define OS_ERR_NONE                     0u

#define RECT_ERR_OUTOFBOUND				1u
#define RECT_ERR_COLOR					2u
#define RECT_ERR_INPUTINVALID			3u
#define RECT_ERR_SIZE					4u

#define ELL_ERR_OUT_OF_BOUND			11u
#define ELL_ERR_COLOR					12u
#define ELL_ERR_INPUTINVALID			13u

#define LINE_ERR_OUTOFBOUND				21u
#define LINE_ERR_COLOR					22u
#define LINE_ERR_INPUTINVALID			23u
#define LINE_ERR_SIZE					24u

#define BIT_ERR_OUT_OF_BOUND			31u

/*
OSMutexPend(MutexHandle, WAIT_FOREVER, &error);
if(error)
{
   	UART_puts("\n\r0:mutexpend error=");
 	UART_putint(error);
 	UART_puts("\n\r");
}
*/



uint8_t STRERR(uint8_t errnum)
{
	switch(errnum) {
		case 1  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

	   case 2  :
		   UART_puts("\nPlease stay within screen boundaries!\n");
		   break;

		case 3  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 4  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 5  :
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;

		case 31:
			UART_puts("\nPlease stay within screen boundaries!\n");
			break;
		default:
			UART_puts("/nPlease note that this error value has no definition");
};
