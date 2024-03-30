# ESP32-based Soil Humidity Sensor
This repository contains details about a Soil Moisture Monitoring System using an ESP32 microcontroller and an OLED display, programmed using Arduino IDE. The system provides real-time monitoring of soil moisture levels and displays the information on the OLED screen. Additionally, it includes a button interface for user interaction.
## Features
- Real-time Monitoring: Continuously monitors soil moisture levels using an analog soil moisture sensor.
- User Interaction: Incorporates a button interface for user interaction, allowing users to trigger specific actions.
- OLED Display: Utilizes an OLED display to represent soil moisture percentage and system status visually.
- Dynamic Display: Implements dynamic text scrolling on the OLED display for longer messages.

## Hardware Requirements

To make this project, you will need the following hardware components (links for exact parts, subject to change):

- ESP32 microcontroller [board](https://www.optimusdigital.ro/ro/placi-cu-esp32/12933-placa-de-dezvoltare-plusivo-wireless-compatibila-cu-esp32-si-ble.html?search_query=0104110000086631&results=1)
- Soil moisture [sensor](https://ardushop.ro/ro/home/1323-senzor-higrometru-capacitiv.html) (We used a capacitive one)
- Push [button](https://ardushop.ro/ro/home/2703-buton-12x12mm.html)
- OLED [display](https://www.optimusdigital.ro/ro/optoelectronice-lcd-uri/1310-modul-oled-albastru-de-091-128x32-px.html?search_query=0104110000012654&results=1) (SSD1306-based, the one in this project is communicating through I2C)
- Through-hole prototyping [board](https://ardushop.ro/ro/breadboards-pcb-expansions/1497-placa-pcb-prototipare-fata-dubla-5x7.html)

## Installation
Ensure you have the necessary libraries installed:
  ### Display ones:
  - Wire.h
  - Adafruit_GFX.h
  - Adafruit_SSD1306.h
  ### ESP32 management:
  - esp32-hal-cpu.h
- Connect the hardware components according to the provided pin definitions in the code.
- Upload the provided sketch to your ESP32 board using the Arduino IDE or your preferred method.
- Once uploaded, the system will begin monitoring soil moisture levels and if the button is pressed, display the information on the OLED screen.

## Configuration
- Pin Definitions: Modify the pin definitions in the code to match your hardware configuration, if necessary.
- Threshold Values: Adjust the DrySoilValue and WateredSoilValue constants according to your soil moisture sensor's calibration.

## Roadmap
- Implement BLE functionality.
- Connect the ESP to a mobile app, and add push notifications for when the RH% is lower than a threshold value.
- Add a battery for cable-free usage.
- Make it possible to use the same ESP with multiple moisture sensors (multiple plants).

## License
  This project is licensed under the [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0.txt).

### Contributing

Contributions are welcome! For major changes, please open an issue first to discuss potential modifications.
