/*
 * ADC0804 Driver — Header
 * Author: Ayush Kumar
 */

#ifndef ADC_H
#define ADC_H

#include <reg52.h>

// ── ADC0804 Pin Definitions ────────────────
sbit ADC_CS   = P3^0;    // Chip select
sbit ADC_RD   = P3^1;    // Read strobe
sbit ADC_WR   = P3^2;    // Write / start conversion
sbit ADC_INTR = P3^3;    // Interrupt — low when done

// ── Data Bus ───────────────────────────────
#define ADC_DATA_PORT  P1  // 8-bit data from ADC

// ── Function Declarations ──────────────────
void          adc_init(void);
unsigned char adc_read(void);
void          delay_ms(unsigned int ms);

#endif // ADC_H
