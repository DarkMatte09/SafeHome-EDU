![SafeHome EDU Banner](image.png)

# SafeHome EDU – Smart IoT Security System

## Overview
SafeHome EDU is an educational smart home security system built using an ESP32-DIV development board with an integrated display. The project demonstrates how a motion detection sensor can communicate with a microcontroller to trigger real-time alerts and notifications. This system serves as a practical introduction to IoT, embedded programming, and basic cybersecurity principles.

The system uses a PIR motion sensor to detect movement. When motion is detected, the ESP32-DIV:
- Updates the display with the current status (SAFE / ALERT)
- Activates an optional buzzer
- Sends a real-time notification to the user via Telegram

This project is suitable for students and beginners learning about embedded systems, IoT, and home security.

---

## Features
- Motion detection using PIR sensor (HC-SR501)
- Real-time status displayed on ESP32-DIV screen
- Instant smartphone notifications via Telegram
- Optional buzzer alarm
- Wi-Fi connectivity for remote communication
- Graphical display interface showing SAFE / ALERT states
- Modular and expandable design

---

## Hardware Requirements
- ESP32-DIV development board with integrated display
- PIR motion sensor (HC-SR501)
- Jumper wires
- Optional buzzer module
- Micro USB cable for ESP32-DIV programming

---

## Wiring Guide

### Connections between PIR sensor and ESP32-DIV
| Component      | ESP32-DIV Pin | Description |
|----------------|---------------|------------|
| PIR OUT        | GPIO 13       | Digital signal sent to ESP32-DIV when motion is detected |
| PIR VCC        | 5V            | Power supply to the PIR sensor |
| PIR GND        | GND           | Ground connection |

### Optional buzzer connection
| Component | ESP32-DIV Pin | Description |
|-----------|---------------|------------|
| Buzzer (+) | GPIO 12       | Positive pin connected to ESP32-DIV |
| Buzzer (–) | GND           | Ground connection |

**Note:** The PIR sensor sends a digital HIGH signal to the ESP32-DIV when motion is detected and LOW when no motion is present. The ESP32-DIV reads this signal to trigger alerts and notifications and to update the display.

---

## Firmware Setup for ESP32-DIV

1. **Install Arduino IDE** (or PlatformIO) on your computer.
2. **Install ESP32 Board Support**:
   - Open Arduino IDE → File → Preferences
   - Add URL: `https://dl.espressif.com/dl/package_esp32_index.json` in *Additional Board Manager URLs*
   - Go to Tools → Board → Board Manager → Search for ESP32 → Install
3. **Select Board**:
   - Tools → Board → “ESP32 Dev Module” (ESP32-DIV compatible)
   - Tools → Port → Select your ESP32-DIV port
4. **Install Required Libraries**:
   - WiFi library (built-in)
   - HTTPClient (built-in)
   - TFT_eSPI (for graphical display)
5. **Configure TFT_eSPI library** if needed to match ESP32-DIV pinout.

---

## Software Setup

1. **Clone the repository**:
```bash
git clone https://github.com/your-username/SafeHome-EDU.git
```
Open the project in Arduino IDE (main.ino).

Configure Wi-Fi and Telegram credentials in main.ino:
```bash
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

String botToken = "YOUR_BOT_TOKEN";
String chatID  = "YOUR_CHAT_ID";
```
Upload firmware to ESP32-DIV via USB.
## Code Overview
- main.ino reads the digital signal from the PIR sensor.
- When motion is detected:
  - The ESP32-DIV sets motionDetected = true.
  - The display updates to ALERT (red).
  - The optional buzzer is activated.
  - A Telegram notification is sent.
- When motion ends (PIR output LOW):
  - motionDetected is reset.
  - The display updates to SAFE (green).
  - Buzzer is deactivated.
- The firmware integrates the TFT_eSPI library to manage the display graphics for the SAFE/ALERT states.

## Using the System
1. Connect the PIR sensor and buzzer to the ESP32-DIV following the wiring guide.
2. Power the ESP32-DIV via USB.
3. Wait for the system to connect to Wi-Fi. Telegram confirms: "System armed and ready."
4. When motion occurs:
  - The display shows ALERT.
  - The buzzer sounds (optional).
  - Telegram sends an alert.
5. Once motion stops, the display returns to SAFE, and the buzzer stops.

## Future Improvements
- Add more sophisticated graphical interface (animations, icons)
- Implement remote arm/disarm via web or app interface
- Event logging for motion history
- Battery-powered portable operation
- Integration with additional sensors (door/window, temperature, etc.)
- Advanced notification rules (time-based alerts, multiple users)

## Learning Objectives
- Understanding IoT system design
- Sensor integration and signal processing
- Wireless communication and notifications
- Real-time alert systems
- Basics of cybersecurity for connected devices
- Practical experience with microcontroller displays

## Project Structure
```bash
SafeHome-EDU/
│── main.ino         # Firmware with display graphics, PIR handling, Telegram notifications
│── README.md        # Project description and setup tutorial
│── images/          # Wiring diagrams, photos of ESP32-DIV and PIR setup
│── docs/            # Optional additional documentation
```
