#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "uart.h"
#include "app.h"
#include "schaduler.h"


uint32_t main(void)
{
	timer0_init();
	UART5_init();
	PORTF_Init();
	while (1)
	{
		start_os();
	}
}

