/*
 * uart_cli.c
 *
 *  Created on: Sep 24, 2026
 *      Author: capunom
 */

#include "uart_cli.h"
#include <string.h>

//volatile memory buffers tracking asynchronous data inputs from ISR
volatile char rx_buff[BUFFER_SIZE];
volatile uint8_t rx_index = 0;
volatile uint8_t command = 0;

void uart2_interrupt_init(void)
{
	// power up GPIOA & USART2
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// map pins PA2 (TX) & PA3 (RX) to alternate function mode (binary 10)
	GPIOA->MODER &= ~((3U << 4 )  | (3U << 6));
	GPIOA->MODER |=  ((2U << 4 )  | (3U << 6));
	// Link pins to  AF7 (USART2) using lower array index
	GPIOA->AFR[0] &= ~(( 0xF << 8 ) | ( 0xF << 12 ));
	GPIOA->AFR[0] |=  ((  7U << 8 ) | ( 7U  << 12 ));
	//compute and load clock division scale inside the Baud Rate Register
	USART2->BRR = 0x16C;
	// enable transmitter (TE), receiver (RE), and receive interrupt (RXNEIE) inside CR1
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;
	USART2->CR1 |= USART_CR1_RXNEIE;
	// enable USART2 peripheral engine (UE)
	USART2->CR1 |= USART_CR1_UE;
	// Unmask the Global Interrupt channel inside the ARM core Nested Vectored Interrupt Controller
    // USART2_IRQn is assigned a hardware vector priority identifier slot of 38
	NVIC_EnableIRQ(USART2_IRQn);
}

void uart2_transmit_char(char c)
{
	while (!(USART2->SR & USART_SR_TXE));
	USART2->DR = c;
}
void uart2_transmit_string(char *string)
{
	while (*string)
	{
	uart2_transmit_char(*string++);
	}
}

// hardware vector ISR
//
void usart2_irqhandler(void)
{
	if (USART2->SR & USART_SR_RXNE)
	{
		char received_char = (char)(USART2->DR); // Reading the DR register automatically clears the RXNE flag!
		// echo back characters to PC screen to show what they are typing
		uart2_transmit_char(received_char);


		// check if user pressed the "Enter" key (\r or \n)
		if (received_char == '\r' || received_char == '\n')
		{
			if (rx_index > 0)
			{
				rx_buff[rx_index] = '\0';
				command = 1;

			}

		}
	else
	{
		// Protect against a buffer overflow crash
				if (rx_index < (BUFFER_SIZE - 1 ))
			{
				rx_buff[rx_index++] = received_char; // store byte and step forward
			}
		}
	}
}



