#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "uart.h"
#include "app.h"
#include "schaduler.h"

uint8_t data_receive[DATA_SIZE]={0,0};
uint8_t ready_flag = 0;
uint8_t i=0;
/*******************************************************************************************************/
/*
   >> UART5 initialization
   >> configure Pin4 and Pin5 of PORTE for UART
*/

void UART5_init (void)
{

SYSCTL_RCGCUART_R |= 0x20;               /* UART5 Enable clock */
SYSCTL_RCGCGPIO_R |= 0x10;               /* PORTE Enable clock */
delay(10);
/* UART5 initialization */
UART5_CTL_R = 0;                         /* disable UART5 */
UART5_IBRD_R = 104;                      /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
UART5_FBRD_R = 11;                       /* fraction part, see Example 4-4 */
UART5_CC_R = 0;                          /* use system clock */
UART5_LCRH_R = 0x60;                     /* 8-bit, no parity, 1-stop bit, no FIFO */
UART5_IM_R |= 0x10;                      /* activate interrupt mode */
NVIC_EN1_R =(1<<29);
UART5_CTL_R = 0x301;                     /* enable UART5, TXE, RXE */


/* UART5 TX0 and RX0 use PE4 and PE5. Set them up. */

GPIO_PORTE_DEN_R |= 0x30;                /* Make PE4 and PE5 as digital */
GPIO_PORTE_AMSEL_R = 0x0;
GPIO_PORTE_AFSEL_R |= 0x30;               /* Use PE4,PE5 alternate function */
GPIO_PORTE_PCTL_R |= 0x00110000;           /* configure PE4 and PE5 for UART */
}
/***********************************************************************************************/
/*******************************************************************************************************/
/*
   >> UART5 ISR
   >> Receive data from another MC using UART5
   >> if data_receive array is full, ready_flag will be one and stop to receive data till APP takes action
*/

void UART5_handler(void)
{
	//if (ready_flag == 0)
	//{
		data_receive[i] = UART5_DR_R;
		i++;

		if (i == 2)
		{
			i = 0;
			ready_flag =1;
		}

	//}
UART5_ICR_R |= (1 << 4);
}

/*******************************************************************************************************/
/*
   >> read data receive
*/

void read_data (uint8_t * data_read,uint8_t size)
{

	uint8_t j;
	for (j = 0; j < size; j++)
	{
		data_read[j] = data_receive[j];
	}
}

uint8_t data_ready (void)
{
	if (ready_flag)
	{
		ready_flag=0;
		return 1;
	}
	else
	{
		return 0;
	}

}







