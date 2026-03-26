/*
 * UART Driver — Implementation
 * Author: Ayush Kumar
 */

#include "uart.h"

// ── Initialize UART ────────────────────────
// Mode 1: 8-bit UART, Timer1 for baud rate
void uart_init(void) {
    TMOD &= 0x0F;       // Clear Timer1 bits
    TMOD |= 0x20;       // Timer1 mode 2 (auto reload)
    TH1   = TH1_VALUE;  // 9600 baud @ 11.0592 MHz
    TL1   = TH1_VALUE;
    TR1   = 1;          // Start Timer1

    SCON  = 0x50;       // Mode 1, REN enabled
    TI    = 1;          // Ready to transmit
}

// ── Send Single Character ──────────────────
void uart_send_char(unsigned char ch) {
    while (TI == 0);    // Wait until ready
    TI   = 0;
    SBUF = ch;          // Load character
}

// ── Send String ───────────────────────────
void uart_send_string(char *str) {
    while (*str != '\0') {
        uart_send_char(*str);
        str++;
    }
}

// ── Send Number as String ──────────────────
void uart_send_number(unsigned char num) {
    unsigned char hundreds, tens, units;

    hundreds = num / 100;
    tens     = (num % 100) / 10;
    units    = num % 10;

    if (hundreds > 0)
        uart_send_char('0' + hundreds);
    if (hundreds > 0 || tens > 0)
        uart_send_char('0' + tens);

    uart_send_char('0' + units);
}
```

3. Commit message:
```
Add uart.c - UART driver for serial debug output at 9600 baud
```

---

## Create `src/relay.h`

1. Filename:
```
src/relay.h
