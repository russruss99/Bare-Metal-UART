/*
 * uart_cli.h
 *
 *  Created on: Sep 24, 2026
 *      Author: capunom
 */

#ifndef INC_UART_CLI_H_
#define INC_UART_CLI_H_

#include "stm32f4xx.h"

//define maximum string parsing constraint
#define BUFFER_SIZE 64

//functions
void uart2_interrupt_init(void);
void uart2_interrupt_char(char c);
void uart2_transmit_string(char *sting);
void usart2_irghandler(void);

#endif /* INC_UART_CLI_H_ */
