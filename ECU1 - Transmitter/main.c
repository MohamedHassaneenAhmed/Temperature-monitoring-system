#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "adc.h"
#include "uart.h"
#include "temperature.h"
#include "schaduler.h"
#include "button.h"

uint32_t main(void)
{
	timer0_init();
	adc_init();
	UART5_init();
	PORTF_Init();
	while (1)
	{
		start_os();
	}
}
