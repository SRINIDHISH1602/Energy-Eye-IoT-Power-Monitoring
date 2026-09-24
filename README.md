# ⚡ Energy Eye – IoT Based Power Monitoring System

An IoT-based smart energy monitoring system using **ESP32**, **ZMPT101B**, **ACS712**, **16×2 I2C LCD**, **Relay Module**, and **Blynk IoT**.

## 📌 Project Overview

Energy Eye is an IoT-based smart energy meter designed to monitor electrical parameters in real time.

The system measures:

- ⚡ Voltage
- 🔌 Current
- 💡 Power
- 🔋 Energy consumption (kWh)
- 💰 Estimated electricity cost

The measured data is displayed locally on a **16×2 I2C LCD** and remotely through the **Blynk IoT dashboard**. A relay module allows remote ON/OFF control of the connected electrical load.

## 🛠️ Hardware Components

- ESP32 Microcontroller
- ZMPT101B AC Voltage Sensor
- ACS712 Current Sensor
- 16×2 I2C LCD
- 5V 1-Channel Relay Module
- AC Load
- Power Supply

## 💻 Software & Technologies

- Arduino IDE
- Embedded C/C++
- ESP32
- Blynk IoT
- Wi-Fi

## 🔧 System Architecture

```text
              AC MAINS
                  │
        ┌─────────┴─────────┐
        │                   │
   ZMPT101B              Relay
 Voltage Sensor             │
        │                   │
        └───────┐     ACS712
                │   Current Sensor
                │         │
                └────┬────┘
                     │
                   ESP32
                ┌────┼────┐
                │    │    │
               LCD  Wi-Fi Relay
                     │
                Blynk Cloud
                     │
                Mobile App


## 🚀 Features

- Real-time voltage monitoring
- Real-time current monitoring
- Power measurement
- Energy consumption monitoring
- Electricity cost estimation
- Local LCD display
- Blynk IoT cloud monitoring
- Remote load ON/OFF control
- Wi-Fi connectivity

## 📱 Blynk Dashboard

The Blynk IoT dashboard displays:

- Voltage
- Current
- Power
- Energy consumption
- Estimated cost
- Relay ON/OFF control

## 📟 ESP32 Pin Configuration

| Component | ESP32 Pin |
|---|---|
| ZMPT101B Voltage Sensor | GPIO34 |
| ACS712 Current Sensor | GPIO35 |
| LCD SDA | GPIO21 |
| LCD SCL | GPIO22 |
| Relay | Digital GPIO |

## 📂 Project Files

| File | Description |
|---|---|
| `energy_eye.ino` | ESP32 source code |
| `project_report.pdf` | Complete project report |
| `README.md` | Project documentation |

## ▶️ How to Run

1. Install **Arduino IDE**.
2. Install ESP32 board support.
3. Install the required libraries.
4. Open `energy_eye.ino`.
5. Enter your Wi-Fi credentials.
6. Enter your Blynk authentication details.
7. Select the correct ESP32 board and COM port.
8. Upload the code to the ESP32.
9. Connect the sensors, LCD and relay.
10. Open the Blynk dashboard to monitor the system.

## ⚠️ Safety

This project involves AC mains voltage.

Do not work with mains wiring unless you are properly trained and qualified. Ensure appropriate isolation, insulation, fusing, and enclosure are used.

## 📄 Project Report

The complete project report is available here:

[View Project Report](project_report.pdf)

## 🔮 Future Scope

- Automated electricity bill generation
- Long-term cloud data storage
- Enhanced data security
- AI-based load prediction
- Energy usage optimization
- Industrial-grade sensing and hardware

## 👨‍💻 Author

**SRINIDHISH1602**

Department of Electronics and Communication Engineering

---

⭐ If you find this project useful, consider giving the repository a star.
