/*
 * Software PWM Driver — Implementation
 * Author: Ayush Kumar
 */

#include "pwm.h"
#include "adc.h"    // For delay_ms

// Current duty cycle (0-100)
static unsigned char current_duty = 0;

// ── Initialize PWM ─────────────────────────
void pwm_init(void) {
    PWM_PIN      = 0;
    current_duty = 0;
}

// ── Set PWM Duty Cycle ─────────────────────
// duty: 0 = fully OFF, 100 = fully ON
void pwm_set_duty(unsigned char duty) {
    unsigned char on_time;
    unsigned char off_time;

    // Clamp to 0-100
    if (duty > 100) duty = 100;
    current_duty = duty;

    if (duty == 0) {
        PWM_PIN = 0;
        return;
    }

    if (duty == 100) {
        PWM_PIN = 1;
        return;
    }

    // Generate one PWM cycle
    // ON time  = duty% of PWM_PERIOD
    // OFF time = remaining period
    on_time  = duty;
    off_time = PWM_PERIOD - duty;

    PWM_PIN = 1;
    delay_ms(on_time);
    PWM_PIN = 0;
    delay_ms(off_time);
}
Add pwm.c - software PWM implementation for motor speed control
