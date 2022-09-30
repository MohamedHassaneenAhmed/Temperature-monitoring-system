#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"
#include "uart.h"
#include "temperature.h"
#include "schaduler.h"
#include "button.h"

uint8_t sys_tick_flag=0;
uint32_t sys_tick=0;

/******************************************************************************************************/
/* determine task and its periodicity */

task_cfg task_array []=
{
 {task_0 , 1500 },                 /* task_0 --->  >> task(0)
                                                   >> ADC Trigger using timer0
                                                   >> get temperature in c degree */

 {task_1 , 2500},                 /* task_1 --->  >> task(1)
                                                  >> read temperature
                                                  >> send temperature using uatr5 if temperature is changed */
 {task_2 , 500 },                 /* task_2 ---> reads button status */
  {task_3 , 1000},                /* task_3 ---> toggle led every 1 second */
};

/*********************************************************************************************************/
/*
   >> timer0 configuration
   >> used for trigger adc
   >> used for system tick
*/
void timer0_init( void)
{
	SYSCTL_RCGCTIMER_R |= 1;                /* Enable clock to Timer block 0 */
    uint8_t delay = SYSCTL_RCGCTIMER_R;
    TIMER0_CTL_R =0;                        /*disable Timer before initialization */
    TIMER0_CFG_R =0x04;                     /* 32-bit option */
	TIMER0_TAMR_R=0x02;                     /* periodic mode and down counter */
	TIMER0_TAILR_R= 16000-1;                /*Timer A interval load value reg. (1 msec) */
	TIMER0_ICR_R = 0x1;                     /* clear the Timer0A timeout flag */
	TIMER0_IMR_R = 0x01;                    /* enable Timer0A timeout interrupt */
	TIMER0_CTL_R |=0x20;                    /*timer trigger */
	TIMER0_CTL_R |=0x01;                    /* Enable clock to Timer block 0 */
	NVIC_EN0_R = (1<<19);
}

/*********************************************************************************************************/
/*
   >> ISR handler
   >> used for update system tick
*/

void TIMER0A_Handler(void)
{
		sys_tick++;
		sys_tick_flag = 1;
		TIMER0_ICR_R = 0x1;
}

/*********************************************************************************************************/
/*
   >> operating system starting
   >> managing application tasks
*/

void start_os (void)
{
	uint8_t i;
	if (sys_tick_flag == 1)
	{
		for ( i=0; i< tasks_size ; i++ )
		{
			if ((sys_tick % task_array[i].periodicity) == 0)
			{
				task_array[i].task_ptr();
			}

		}

sys_tick_flag =0;
	}

}
