#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"
#include "uart.h"
#include "temperature.h"
#include "schaduler.h"
#include "button.h"

/*******************************************************************************************************/
/*
   >> UART5 initialization
   >> configure Pin4 and Pin5 of PORTE for UART
*/

void UART5_init (void)
{

SYSCTL_RCGCUART_R |= 0x20;               /* UART5 Enable clock */
SYSCTL_RCGCGPIO_R |= 0x10;               /* PORTE Enable clock */

/* UART5 initialization */
UART5_CTL_R = 0;                         /* disable UART5 */
UART5_IBRD_R = 104;                      /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
UART5_FBRD_R = 11;                       /* fraction part, see Example 4-4 */
UART5_CC_R = 0;                          /* use system clock */
UART5_LCRH_R = 0x60;                     /* 8-bit, no parity, 1-stop bit, no FIFO */
UART5_CTL_R = 0x301;                     /* enable UART5, TXE, RXE */


/* UART5 TX0 and RX0 use PE4 and PE5. Set them up. */

GPIO_PORTE_DEN_R |= 0x30;                /* Make PE4 and PE5 as digital */
GPIO_PORTE_AMSEL_R = 0x0;
GPIO_PORTE_AFSEL_R |= 0x30;               /* Use PE4,PE5 alternate function */
GPIO_PORTE_PCTL_R |= 0x00110000;           /* configure PE4 and PE5 for UART */
}

/****************************************************************************************************************/
/* function transmits data by uart5 */

void UART5Tx(uint32_t t)
{
	while (UART5_FR_R & (1 << 5) != 0)                            /* wait until Tx buffer not full */
	{
	}
	UART5_DR_R = t;                                               /* before giving it another byte */

}



