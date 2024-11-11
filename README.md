# SCP
Smart connected products class project - Group 4

# Smart Alarm Clock Splash Application

This project is a smart alarm clock application designed to interact with an ESP32 microcontroller to create an IoT-enabled device. The microcontroller is connected to The Things Network (TTN) via LoRaWAN and allows users to configure settings for a unique alarm feature: a water-splash mechanism that activates if the alarm is not turned off. The application includes a web interface where users can set alarm time, adjust the water pump power, and monitor the water level.

## Project Overview

The Smart Alarm Clock Splash application combines web and IoT technologies to create a unique and customizable alarm experience. Key functionalities include:

- **Alarm Settings**: Set the alarm time and configure the water pump's power via the web application.
- **Water Level Monitoring**: Check the remaining water level in the container to ensure the splash mechanism is functional.
- **Automatic Splash Mechanism**: If the alarm isn’t turned off, the water pump is triggered to splash water as an extra wake-up measure.

## Technology Stack

### Frontend

- **Vue.js**: Provides a lightweight and interactive UI for alarm settings and monitoring.

### Backend

- **Node.js with Express**: Handles backend logic and routes, connecting with the ESP32 through TTN.

### IoT & Microcontroller

- **ESP32 with LoRa**: The ESP32 microcontroller is connected to The Things Network (TTN) using LoRaWAN to enable long-range communication.
- **LoRaWAN**: A low-power, long-range wireless protocol used to communicate between the ESP32 and the web application via TTN.
- **The Things Network (TTN)**: Provides the LoRaWAN network to handle data transmissions.

## Features

1. **Alarm Time Configuration**: Set the alarm time via the web application.
2. **Adjustable Water Pump Power**: Control the intensity of the water pump used for the splash feature.
3. **Water Level Monitoring**: View the water level to ensure the splash feature will activate when needed.
4. **LoRaWAN Communication**: The ESP32 communicates with the web application through TTN, making it suitable for low-power IoT setups.

## Setup and Installation

### Prerequisites

1. **ESP32 Microcontroller**: Flash the code for LoRaWAN connectivity and device communication.
2. **TTN Account**: Set up a TTN application and connect it to your ESP32.
3. **Web Application**: Ensure you have Node.js and Vue CLI installed.
