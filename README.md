# LW-Clock (Clock, Weather, temperature, humidity, atmospheric pressure, creeping line, remote monitoring)LW-Clock (Clock, Weather, temperature, humidity, atmospheric pressure, creeping line, remote monitoring)
Compact clock has a variety of functions: Perfect time, Alarm, Measurement of temperature, humidity and atmosphere pressure indoors, Forecasting download, Upload submission to MQTT & Thingspeak server, Display of any predetermined information at set time. Clock has low power consumption and provides high display brightness.

------------
## What is a LW-Clock?
LW-Clock is a device, based on ESP8266 microcontroller and real-time clock DS3231. It uses indicator modules MAX7919 for information output. BME280 sensor provides a precise measurement of indoor temperature, humidity and barometric pressure. The device has a spare slots to connect other sensors via I2C and UART protocols. An Internet connection via Wi-Fi module helps to synchronize time with NTP servers, to get and display forecast, news, exchange rate etc. Data from sensors can be transmitted via MQTT protocol or displayed on popular monitoring service thingspeak.com.
Clock can display predetermined information (reminders, greetings, advertisements, time-schedules etc.) according on schedule. Display of text messages, transmitted from any place via MQTT is also possible. 
Clock adjustment and manipulation is performed via WEB-interface. Micro-USB connector allows to use any low-duty USB-charger to power the device.

# Features include:
- Always precise time because of synchronization with NTP time servers
- High display brightness 
- Indoor temperature, humidity and barometric pressure measurement
- Sending temperature, humidity and barometric pressure data to MQTT server
- Getting a weather information and forecast for your city (temperature, barometric pressure, humidity, cloud and wind structure) 
- Output of any predetermined information in the form of a creeping line
- Remote transmission of any text messages via MQTT server and it’s output on the clock
- No buttons – control the clock via WEB-interface from PC, tablet or smartphone
- Brightness and speed of output adjustment
- Two alarm clocks
- Firmware update via Wi-Fi
- Information display on 3 languages: English, Russian, Bulgarian
- Tree types of case material: PETG plastic, acryl or wood 
- Powered via USB
- Normal USB port or phone charger
- An option to install different alternative Open Source firmware, designed to MAX7912 matrix control
- Hackable: Open source hardware and firmware, Displays information read via UART

## Required Parts:
Wemos D1 Mini: http://got.by/40d3u7 
Dot Matrix Module MAX7219: http://got.by/40da6v 
BME280 Digital Sensor (Temperature, Humidity, Barometric Pressure) 5V: http://got.by/40d52x 
TTP223B digital touch capacitive  sensor: http://got.by/40d6kz
DS3231 AT24C32 IIC Module Precision Clock http://got.by/42k10g
Active Buzzer http://got.by/42k1sg
Micro USB Cable: http://got.by/40dbf7 
Note: Using the links provided here help to support these types of projects. Thank you for the support.