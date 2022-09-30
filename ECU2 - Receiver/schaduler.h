/*
 * schaduler.h
 *
 *  Created on: Jan 5, 2022
 *      Author: tiba
 */

#ifndef SCHADULER_H_
#define SCHADULER_H_

#define tasks_size sizeof(task_array)/sizeof(task_cfg)

void timer0_init( void);
void TIMER0A_Handler(void);
void start_os (void);
void delay(uint32_t number_of_Mseconds);


 typedef struct
 {
	 void (*task_ptr) (void);
	 uint16_t periodicity ;
 } task_cfg;


#endif /* SCHADULER_H_ */
