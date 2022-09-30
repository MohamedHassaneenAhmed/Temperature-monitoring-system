#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"
#include "uart.h"
#include "temperature.h"
#include "schaduler.h"
#include "button.h"

uint8_t temperature=0;


/********************************************************************************************************************/
/*
   >> task(0)
   >> ADC Trigger using timer0
   >> get temperature in c degree
*/
void task_0 (void)
{
	while((ADC0_RIS_R & 8) == 0) ;                                   /* wait for conversion complete */
	temperature = (147.5 - (247.5 * ADC0_SSFIFO3_R) / 4096.0);       /* calculating temperature in degree */
	ADC0_ISC_R = 8;                                                    /* clear completion flag */
}

/**********************************************************************************************************************/
/* read temperature */
uint8_t temperature_read (void)
{

	return temperature;
}


/************************************************************************************************************************/
/*
   >> task(1)
   >> read temperature
   >> send temperature using uatr5 if temperature is changed
*/
uint8_t new_temperature;
uint8_t current_temperature=0;

void task_1 (void)
{

	new_temperature = temperature_read();
	if( new_temperature != current_temperature)
	{
		UART5Tx(SID_TEMP);
		delay(1);
		UART5Tx(new_temperature);
	}
	current_temperature = new_temperature ;
}

