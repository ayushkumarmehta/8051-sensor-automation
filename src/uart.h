/*
 * UART Driver — Header
 * Author: Ayush Kumar
 */

#ifndef UART_H
#define UART_H

#include <reg52.h>

// ── UART Configuration ─────────────────────
// Crystal: 11.0592 MHz, Baud: 9600
#define BAUD_RATE    9600
#define TH1_VALUE    0xFD   // Timer1 reload for 9600 baud

// ── Function Declarations ──────────────────
void uart_init(void);
void uart_send_char(unsigned char ch);
void uart_send_string(char *str);
void uart_send_number(unsigned char num);

#endif // UART_H
