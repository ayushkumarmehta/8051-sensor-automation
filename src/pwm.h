/*
 * Software PWM Driver — Header
 * Author: Ayush Kumar
 */

#ifndef PWM_H
#define PWM_H

#include <reg52.h>

// ── PWM Output Pin ─────────────────────────
sbit PWM_PIN = P2^1;    // Motor/fan control

// ── PWM Configuration ──────────────────────
#define PWM_PERIOD    100   // PWM period in ms (100Hz)

// ── Function Declarations ──────────────────
void pwm_init(void);
void pwm_set_duty(unsigned char duty);  // 0-100%

#endif // PWM_H
```

4. Commit message:
```
Add pwm.h - PWM pin definition and declarations
```
5. Click **"Commit new file"**

---

## Then Create `src/pwm.c`

1. Click **"Add file"** → **"Create new file"**
2. Filename:
```
src/pwm.c
