#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"
#include "uart.h"
#include "temperature.h"
#include "schaduler.h"
#include "button.h"


uint8_t button_status;

/* PORTF0 has special function, need to unlock to modify */
/*******************************************************************************************/
void PORTF_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;                /* activate clock for Port F */
	uint8_t delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;             /* unlock commit register */
	GPIO_PORTF_CR_R = 0x01;                     /* make PORTF0 configurable */
	GPIO_PORTF_LOCK_R = 0;                      /* lock commit register */
	GPIO_PORTF_PUR_R = 0x11;                    /* Enable pull up resistors on PF4,PF0*/
	GPIO_PORTF_DIR_R = 0x0E;                    /* PF4,PF0 input*/
	GPIO_PORTF_DEN_R = 0x1F;                    /* Enable digital pins PF4-PF0 */
}

/********************************************************************************************/
 /* task_2 ---> reads button status */
void task_2 (void)
{
	button_status = GPIO_PORTF_DATA_R & 0x01;
}

/********************************************************************************************/
uint8_t button_read (void)
{
	return button_status;
}

/*********************************************************************************************/
/* task_3 ---> toggle led every change of button status */
uint8_t new_status=0,current_status=0;


void task_3 (void)
{

	new_status = button_read();
	if( new_status != current_status)
	{

		GPIO_PORTF_DATA_R ^= 0x0E;
		UART5Tx(SID_BUTTON);
		delay(1);
		UART5Tx(BUTTON_ACTION);


	}
	current_status = new_status ;
}
