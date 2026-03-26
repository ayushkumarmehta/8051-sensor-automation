/*
 * ADC0804 Driver — Implementation
 * Author: Ayush Kumar
 */

#include "adc.h"

// ── Initialize ADC0804 ─────────────────────
void adc_init(void) {
    ADC_CS   = 1;    // Deselect ADC
    ADC_RD   = 1;    // Read inactive
    ADC_WR   = 1;    // Write inactive
    ADC_DATA_PORT = 0xFF;  // Set port as input
}

// ── Read ADC Value ─────────────────────────
// Returns 8-bit digital value (0-255)
unsigned char adc_read(void) {
    unsigned char adc_val;

    // Step 1 — Start conversion
    ADC_CS = 0;       // Select ADC
    ADC_WR = 0;       // Pulse WR low
    delay_ms(1);
    ADC_WR = 1;       // WR high — conversion starts

    // Step 2 — Wait for conversion complete
    // INTR goes LOW when done
    while (ADC_INTR == 1);

    // Step 3 — Read data
    ADC_RD = 0;                  // Enable output
    delay_ms(1);
    adc_val = ADC_DATA_PORT;     // Read 8-bit value
    ADC_RD = 1;                  // Disable output
    ADC_CS = 1;                  // Deselect ADC

    return adc_val;
}

// ── Millisecond Delay ──────────────────────
// For 11.0592 MHz crystal
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 112; j++);
}
Add adc.c - ADC0804 read implementati
