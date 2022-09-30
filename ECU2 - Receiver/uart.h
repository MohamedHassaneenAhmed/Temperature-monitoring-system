/*
 * uart.h
 *
 *  Created on: Dec 28, 2021
 *      Author: tiba
 */

#ifndef UART_H_
#define UART_H_


#define DATA_SIZE 2
 uint8_t data_read[2];

char UART5Rx(void);
void UART5_init (void);
void UART5_handler (void);
void read_data (uint8_t * data_read,uint8_t size);
uint8_t data_ready (void);

#endif /* UART_H_ */
