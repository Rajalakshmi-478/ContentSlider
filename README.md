"# ContentSlider" 
# 🔄 RFID + Rotary Encoder with JSON Output

## 📘 Overview
This project uses an **Arduino/ESP32** board to read data from:
- An **RFID module (MFRC522)** for card/tag detection  
- A **rotary encoder** for position tracking  

The device outputs the **encoder position (A)** and **RFID UID** as a **JSON string** via the Serial Monitor.  
It also lights up LEDs based on the encoder’s position limits.

---

## ⚙️ Hardware Components
| Component | Description |
|------------|--------------|
| **Arduino/ESP32** | Main controller board |
| **MFRC522 RFID Module** | Reads RFID card UID |
| **Rotary Encoder** | Detects rotation and position |
| **2 LEDs** | Indicate encoder min/max limits |
| **Breadboard & Jumpers** | For circuit connections |

---

## 🔌 Pin Connections

| Component | Pin | Description |
|------------|-----|-------------|
| **Encoder A** | D2 | Encoder signal A |
| **Encoder B** | D3 | Encoder signal B |
| **LED 1** | D9 | Lights up at max encoder value |
| **LED 2** | D8 | Lights up at min encoder value |
| **RFID SS** | D10 | Slave Select pin |
| **RFID RST** | D5 | Reset pin |
| **RFID MOSI** | 11 | SPI MOSI |
| **RFID MISO** | 12 | SPI MISO |
| **RFID SCK** | 13 | SPI Clock |
| **VCC** | 3.3V | Power |
| **GND** | GND | Ground |

> Note: Adjust pin numbers in the code if you’re using a different microcontroller.

---

## 🧠 Features
✅ Reads encoder rotation and outputs its position (`A`)  
✅ Detects RFID card UIDs and stores them in memory  
✅ Displays both encoder and UID data as JSON via Serial  
✅ Turns ON:
- **LED1** when encoder reaches max value (200)  
- **LED2** when encoder reaches min value (0)  
✅ Ignores duplicate RFID card reads (stores each UID once)  
✅ Resets encoder position when a new RFID card is detected  

---

## 📄 JSON Output Example
Example Serial Monitor output:
```json
{
  "A": 150,
  "UID": "A1B2C3D4"
}
