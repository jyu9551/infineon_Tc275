/*
 * uart.h
 *
 *  Created on: 2024. 6. 27.
 *      Author: user
 */

#ifndef UART_H_
#define UART_H_

#include "IfxAsclin_Asc.h"

extern void _init_uart3(void);
extern void _out_uart3(const unsigned char _s);
extern unsigned char _in_uart3(void);

#endif /* UART_H_ */
