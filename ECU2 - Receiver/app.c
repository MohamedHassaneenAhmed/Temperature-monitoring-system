#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "uart.h"
#include "app.h"
#include "schaduler.h"

/* PORTF0 has special function, need to unlock to modify */
/*******************************************************************************************/
void PORTF_Init(void)
{
	SYSCTL_RCGCGPIO_R |= 0x20;                /* activate clock for Port F */
    delay (10);
	GPIO_PORTF_LOCK_R = 0x4C4F434B;             /* unlock commit register */
	GPIO_PORTF_CR_R = 0x01;                     /* make PORTF0 configurable */
	GPIO_PORTF_LOCK_R = 0;                      /* lock commit register */
	GPIO_PORTF_PUR_R = 0x11;                    /* Enable pull up resistors on PF4,PF0*/
	GPIO_PORTF_DIR_R = 0x0E;                    /* PF4,PF0 input*/
	GPIO_PORTF_DEN_R = 0x1F;                    /* Enable digital pins PF4-PF0 */
}

/********************************************************************************************/
/*
   >> task(0)" application task '
   >> determine task based on SID if SID=5 --> temperature display, if SID=10 --> botton action
*/
uint8_t SID=0;
uint8_t temperature=0;
uint8_t button_data;
uint8_t data_read[2];

void task_0(void)
{
if(data_ready())
{
		read_data(data_read,DATA_SIZE);
		SID = data_read[0];
		if (SID == 0)
		{
			temperature = data_read[1];
			//ready_flag = 0;
		}
		if (SID == 1)
		{
			button_data = data_read[1];
			GPIO_PORTF_DATA_R ^= button_data;
			//ready_flag = 0;
		}
}
}

