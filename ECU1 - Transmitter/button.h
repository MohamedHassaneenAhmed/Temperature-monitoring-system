/*
 * button.h
 *
 *  Created on: Jan 6, 2022
 *      Author: tiba
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#define SID_BUTTON 1
#define BUTTON_ACTION 0x0E

extern void task_2 (void);
extern void task_3 (void);
extern uint8_t button_read (void);
void PORTF_Init(void);




#endif /* BUTTON_H_ */
