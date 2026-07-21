# ESP32 Radar Scanner

A low-cost ultrasonic radar scanning system based on the ESP32-WROOM-32 development board.

This project uses an ESP32 to control a servo motor and HC-SR04 ultrasonic sensor for 180-degree scanning. The measured distance data is transmitted to a PC through serial communication. Python and Pygame are used to create a real-time radar visualization interface.

---

## Features

- 180-degree servo scanning
- Real-time distance measurement using HC-SR04 ultrasonic sensor
- Serial communication between ESP32 and PC
- Real-time radar visualization using Python and Pygame
- PWM control of passive buzzer for distance warning
- Modular embedded code structure


---

## Hardware

| Component | Description |
|---|---|
| Microcontroller | ESP32-WROOM-32 |
| Ultrasonic Sensor | HC-SR04 |
| Servo Motor | Servo Motor |
| Buzzer | Passive Buzzer |


---

## Development Environment

### ESP32

- VSCode
- PlatformIO
- Arduino Framework
- ESP32Servo library


### PC

- Python 3.13
- Pygame
- PySerial


---

## Project Structure


ESP32-Radar-Scanner
│
├── src
│ └── main.cpp
│
├── lib
│ ├── Servo
│ ├── HCSR04
│ └── Buzzer
│
├── radar.py
│
├── platformio.ini
│
└── README.md



---

## Working Principle


Servo rotates
|
↓
HC-SR04 measures distance
|
↓
ESP32 processes data
|
↓
Serial communication
|
↓
Python + Pygame radar display



---

## Pin Configuration

### HC-SR04

| HC-SR04 | ESP32 |
|---|---|
| Trig | GPIO27 |
| Echo | GPIO14 |


### Servo

| Servo | ESP32 |
|---|---|
| Signal | GPIO13 |


### Passive Buzzer

| Buzzer | ESP32 |
|---|---|
| Signal | GPIO4 |


---

## How to Run

### ESP32

1. Open this project with VSCode + PlatformIO.

2. Upload the firmware to ESP32.


### Python

Install required libraries:

```bash
pip install pygame pyserial

Run:    
python radar.py
```

### Future Improvements

WiFi wireless communication
Web radar interface
Target tracking algorithm
OLED/TFT display
License

MIT License

### Author

Zane