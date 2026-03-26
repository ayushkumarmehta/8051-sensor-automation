/*
 * Relay Driver — Implementation
 * Author: Ayush Kumar
 */

#include "relay.h"

// ── Initialize Relay ───────────────────────
void relay_init(void) {
    RELAY_PIN = 0;    // Start with relay OFF
}

// ── Turn Relay ON ──────────────────────────
// Activates connected load (fan, pump, light)
void relay_on(void) {
    RELAY_PIN = 1;
}

// ── Turn Relay OFF ─────────────────────────
void relay_off(void) {
    RELAY_PIN = 0;
}

// ── Toggle Relay State ─────────────────────
void relay_toggle(void) {
    RELAY_PIN = ~RELAY_PIN;
}
```

3. Commit message:
```
Add relay.c - relay switching driver for load control
```

---

## Finally Create `schematics/README.md` and `docs/README.md`

### `schematics/README.md`
1. Filename:
```
schematics/README.md
