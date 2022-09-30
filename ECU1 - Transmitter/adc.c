#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"
#include "uart.h"
#include "temperature.h"
#include "schaduler.h"
#include "button.h"

void delay(uint32_t number_of_Mseconds);

/***********************************************************************************************/
/*
   >> ADC0 initialization
   >> Timer trigger
*/
void adc_init(void)
{
	SYSCTL_RCGCADC_R|=1;             /* enable clock to ADC0 */
	delay(1);
	ADC0_ACTSS_R &= ~0x08;           /* disable SS3 during configuration */
	ADC0_EMUX_R &= ~0xF000;
	ADC0_EMUX_R |= 0x5000;           /* timer trigger conversion seq 0 */
	ADC0_SSMUX3_R = 0;               /* get input from channel 0 */
	ADC0_SSCTL3_R= 0x0E;             /* take one sample at a time, set flag at 1st sample */
	ADC0_ACTSS_R |= 0x08;            /* enable ADC0 sequencer 3 */
}

/******************************************************************************************************/
/* function delay in millisecond   */

void delay(uint32_t number_of_Mseconds)
{
	uint32_t i;
	for (i = 0; i < number_of_Mseconds; i++)
	{
		NVIC_ST_RELOAD_R = 16000 - 1;
		NVIC_ST_CTRL_R = 5;
		while ((NVIC_ST_CTRL_R & 0x10000) == 0)
		{
		}
		NVIC_ST_CTRL_R = 0;
	}
}



