/*
 * Relay Driver — Header
 * Author: Ayush Kumar
 */

#ifndef RELAY_H
#define RELAY_H

#include <reg52.h>

// ── Relay Pin Definition ───────────────────
sbit RELAY_PIN = P2^0;   // Relay control pin

// ── Function Declarations ──────────────────
void relay_init(void);
void relay_on(void);
void relay_off(void);
void relay_toggle(void);

#endif // RELAY_H
```

3. Commit message:
```
Add relay.h - relay pin definition and declarations
```

---

## Create `src/relay.c`

1. Filename:
```
src/relay.c
