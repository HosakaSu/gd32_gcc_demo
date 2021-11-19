#ifndef __UART_H
#define __UART_H

#include "gd32f10x.h"

void usart0_init(void);
void usart0_send_data_bit(uint8_t buf);
void usart0_send_buf(uint8_t *sendbuf, uint8_t bufcnt);
#endif __UART_H