/*
 * Sensor-Based Automation System
 * Platform : 8051 (AT89S52)
 * Crystal  : 11.0592 MHz
 * Author   : Ayush Kumar
 * Date     : 2025
 */

#include <reg52.h>
#include "adc.h"
#include "pwm.h"
#include "uart.h"
#include "relay.h"

// ── Threshold Configuration ────────────────
#define HIGH_TEMP_THRESHOLD   40    // °C — relay ON
#define LOW_TEMP_THRESHOLD    30    // °C — fan starts

// ── Status LEDs ────────────────────────────
sbit LED_RED   = P2^2;    // High temp warning
sbit LED_GREEN = P2^3;    // Normal status

// ── Function Prototypes ────────────────────
void system_init(void);
void process_sensor(unsigned char adc_val);
unsigned char adc_to_celsius(unsigned char adc_val);

// ── Main Program ───────────────────────────
void main(void) {
    unsigned char adc_value;
    unsigned char temperature;

    system_init();
    uart_send_string("[8051] System Initialised...\r\n");

    while (1) {
        // Read temperature from ADC
        adc_value   = adc_read();
        temperature = adc_to_celsius(adc_value);

        // Control logic
        process_sensor(temperature);

        // Send data over UART
        uart_send_string("[8051] Temp: ");
        uart_send_number(temperature);
        uart_send_string("C\r\n");

        // Small delay before next reading
        delay_ms(500);
    }
}

// ── System Initialisation ──────────────────
void system_init(void) {
    uart_init();
    adc_init();
    pwm_init();
    relay_init();

    LED_RED   = 0;
    LED_GREEN = 1;    // Green ON = system normal
}

// ── Sensor Processing & Control ───────────
void process_sensor(unsigned char temp) {
    if (temp > HIGH_TEMP_THRESHOLD) {
        relay_on();
        pwm_set_duty(100);
        LED_RED   = 1;
        LED_GREEN = 0;
    }
    else if (temp > LOW_TEMP_THRESHOLD) {
        relay_off();
        // Map temp to PWM: 30°C=30%, 40°C=100%
        unsigned char duty = (temp - LOW_TEMP_THRESHOLD) * 7;
        pwm_set_duty(duty);
        LED_RED   = 0;
        LED_GREEN = 1;
    }
    else {
        relay_off();
        pwm_set_duty(0);
        LED_RED   = 0;
        LED_GREEN = 1;
    }
}

// ── ADC Value to Celsius Conversion ───────
// LM35: 10mV/°C, ADC ref = 2.56V
// Temp = (adc_val / 256) * 256 * 0.1 = adc_val * 0.1
unsigned char adc_to_celsius(unsigned char adc_val) {
    return (unsigned char)(adc_val * 0.0977f);
}
Add main.c - core control logic with threshold based automation
