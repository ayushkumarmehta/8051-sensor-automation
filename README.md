# ⚙️ Sensor-Based Automation using 8051 Microcontroller

![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Platform](https://img.shields.io/badge/Platform-8051-blue)
![Language](https://img.shields.io/badge/Language-Embedded%20C-green)
![Domain](https://img.shields.io/badge/Domain-Automation-orange)

> Sensor-based automation prototype using 8051 microcontroller with ADC,
> PWM motor control, UART communication, and relay-based load switching.

---

## 📌 Table of Contents
- [Overview](#-overview)
- [How It Works](#-how-it-works)
- [Hardware Required](#-hardware-required)
- [Circuit Diagram](#-circuit-diagram)
- [Pin Connections](#-pin-connections)
- [Software & Tools](#-software--tools)
- [Project Structure](#-project-structure)
- [Getting Started](#-getting-started)
- [Results](#-results)
- [Future Scope](#-future-scope)
- [Author](#-author)

---

## 📖 Overview

This project implements a **sensor-driven automation system** on the classic
8051 microcontroller. It reads analog sensor data via an **ADC0804**, controls
a DC motor/fan speed using **PWM**, communicates debug data over **UART**, and
switches high-power loads through a **relay module** — all based on
programmable threshold logic.

Real-world applications include:
- Industrial temperature-based fan control
- Automatic irrigation systems
- Smart street lighting
- Factory floor safety automation

---

## ⚙️ How It Works
```
  [Temperature Sensor]──►[ADC0804]──►[8051 MCU]──►[Relay Module]──►[Load ON/OFF]
  [LDR / Proximity  ]──►[ADC0804]──►[8051 MCU]──►[PWM Output  ]──►[Motor Speed]
                                          │
                                          ▼
                                   [UART TX Pin]
                                          │
                                          ▼
                                  [PC Serial Monitor]
                                  (Debug / Logging)
```

### Control Logic
```
IF temperature > HIGH_THRESHOLD:
    relay = ON         (activate cooling load)
    pwm_duty = 100%    (full fan speed)

ELSE IF temperature > LOW_THRESHOLD:
    relay = OFF
    pwm_duty = mapped(temperature, LOW, HIGH, 30%, 100%)

ELSE:
    relay = OFF
    pwm_duty = 0%      (fan off)
```

---

## 🛠 Hardware Required

| Component | Specification | Quantity |
|---|---|---|
| 8051 Microcontroller | AT89S52 / AT89C51 | 1 |
| ADC | ADC0804 (8-bit) | 1 |
| Temperature Sensor | LM35 (analog, 10mV/°C) | 1 |
| Proximity/LDR Sensor | LDR with voltage divider | 1 |
| Relay Module | 5V single channel relay | 1 |
| DC Motor / Fan | 5V DC motor | 1 |
| Motor Driver | L293D / ULN2003 | 1 |
| Crystal Oscillator | 11.0592 MHz | 1 |
| Capacitors | 33pF (×2), 10µF | 3 |
| Resistors | 10kΩ, 1kΩ assorted | — |
| LED Indicators | 5mm red/green | 4 |
| 16x2 LCD Display | HD44780 compatible | 1 |
| Breadboard + Wires | — | — |
| 5V Power Supply | — | 1 |

---

## 🔌 Circuit Diagram

> 📁 See `/schematics/8051_automation_circuit.png`

---

## 📍 Pin Connections

### ADC0804 → 8051
| ADC0804 Pin | 8051 Pin | Function |
|---|---|---|
| DB0–DB7 | P1.0–P1.7 | 8-bit data bus |
| CS | P3.0 | Chip select |
| RD | P3.1 | Read strobe |
| WR | P3.2 | Write/start conversion |
| INTR | P3.3 | Interrupt on completion |
| VIN+ | LM35 output | Analog input |

### Relay & Motor
| Component | 8051 Pin | Function |
|---|---|---|
| Relay IN | P2.0 | Load switching |
| PWM Output | P2.1 | Motor speed control |
| LED 1 (Red) | P2.2 | High temp indicator |
| LED 2 (Green) | P2.3 | Normal status |

### UART
| Signal | 8051 Pin |
|---|---|
| TX | P3.1 (TXD) |
| RX | P3.0 (RXD) |
| Baud Rate | 9600 bps |

---

## 💻 Software & Tools

| Tool | Purpose |
|---|---|
| Keil uVision 5 | Embedded C IDE for 8051 |
| Proteus 8 | Circuit simulation |
| Flash Magic | Hex file flashing to 8051 |
| Arduino IDE (Serial Monitor) | UART debug output |

---

## 📁 Project Structure
```
8051-sensor-automation/
│
├── src/
│   ├── main.c          # Main control logic
│   ├── adc.c           # ADC0804 read functions
│   ├── adc.h
│   ├── pwm.c           # Software PWM implementation
│   ├── pwm.h
│   ├── uart.c          # UART communication
│   ├── uart.h
│   └── relay.c         # Relay switching logic
│   └── relay.h
│
├── schematics/
│   └── 8051_automation_circuit.png
│
├── simulation/
│   └── proteus_simulation.pdsprj
│
├── docs/
│   └── README.md
│
├── README.md
└── LICENSE
```

---

## 🚀 Getting Started

### 1. Clone the Repository
```bash
git clone https://github.com/YOUR_USERNAME/8051-sensor-automation.git
```

### 2. Open in Keil uVision
- File → Open Project → select `src/main.c`
- Set target device: **AT89S52**
- Crystal frequency: **11.0592 MHz**

### 3. Configure Thresholds
In `main.c` adjust these values for your environment:
```c
#define HIGH_TEMP_THRESHOLD   40    // °C — relay ON above this
#define LOW_TEMP_THRESHOLD    30    // °C — fan starts above this
#define BAUD_RATE             9600  // UART baud rate
```

### 4. Build and Flash
- Build → **F7** in Keil
- Open Flash Magic → select COM port → flash `.hex` file

### 5. Monitor Output
Open any serial monitor at **9600 baud** to see:
```
[8051 ANC] System Init...
[8051 ANC] Temp: 32C | PWM: 45% | Relay: OFF
[8051 ANC] Temp: 41C | PWM: 100% | Relay: ON
```

---

## 📊 Results

| Test Condition | ADC Output | PWM Duty | Relay |
|---|---|---|---|
| Temp < 30°C | < 120 counts | 0% | OFF |
| Temp = 35°C | ~178 counts | 50% | OFF |
| Temp > 40°C | > 204 counts | 100% | ON |

---

## 🔭 Future Scope

- Replace ADC0804 with onboard ADC of **PIC or STM32** for better resolution
- Add **LCD display** for real-time sensor readout
- Implement **closed-loop PID control** for precise temperature regulation
- Migrate to **ESP32** for Wi-Fi based remote monitoring
- Design custom **PCB** for compact deployment

---

## 👨‍💻 Author

**Ayush Kumar**
B.Tech — Electronics & Communication Engineering
Vinoba Bhave University, Hazaribagh
GATE 2025 Qualified (ECE) — Score: 428 | AIR: 5568

📧 ayushraj822124@gmail.com
🔗 [LinkedIn](www.linkedin.com/in/ayush-kumar7070)


---

## 📄 License

This project is licensed under the MIT License — see [LICENSE](LICENSE) for details.

---
*If you found this project useful, consider giving it a ⭐ on GitHub!*
```

5. Scroll down → Commit message:
```
Add professional README with circuit details and control logic
