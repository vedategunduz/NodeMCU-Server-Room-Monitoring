# NodeMCU-Server-Room-Monitoring
This project monitors the temperature and humidity of a server room and checks for water leakage using NodeMCU. The data is sent to a PHP server via Wi-Fi.

## Components Used
- NodeMCU
- DHT11 temperature and humidity sensor
- Water sensor
- I2C LCD

## Required libraries
- ESP8266WiFi
- WiFiClient
- ESP8266HTTPClient
- Wire
- LiquidCrystal_I2C
- DHT

## Setup

1. Before starting, ensure that you have installed the CP2102 driver for NodeMCU. You can download it from [here](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads).
1. Connect NodeMCU to your computer and open Arduino IDE.
2. Upload the following [code](nodemcu.ino) to NodeMCU:
3. Place the following PHP script on your server:
```PHP
  <?php
    if($_POST)
      print_r($_POST);
    else
      echo "NO POST";
```

## Variables sent with post
- humidity
- temperature
- waterLevel

The server response will be displayed in the serial monitor.
