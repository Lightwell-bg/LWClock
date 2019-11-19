# LW-Clock (Clock, Weather, temperature, humidity, atmospheric pressure, creeping line, remote monitoring)
Compact clock has a variety of functions: Perfect time, Alarm, Measurement of temperature, humidity and atmosphere pressure indoors, Forecasting download, Upload submission to MQTT & Thingspeak server, Display of any predetermined information at set time. Clock has low power consumption and provides high display brightness.

------------
## What is a LW-Clock?
LW-Clock is a device, based on ESP8266 microcontroller and real-time clock DS3231. It uses indicator modules MAX7919 for information output. BME280 sensor provides a precise measurement of indoor temperature, humidity and barometric pressure. An Internet connection via Wi-Fi module helps to synchronize time with NTP servers, to receive and display forecast, news, exchange rate etc. Data from sensors can be transmitted via MQTT protocol or displayed on popular monitoring service thingspeak.com.
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
- Brightness and output speed of adjustment
- Two alarm clocks
- Firmware update via Wi-Fi
- Information display on 3 languages: English, Russian, Bulgarian
- Three types of case material: PETG plastic, acryl and wood 
- Powered via USB
- Normal USB port or phone charger
- An option to install different alternative Open Source firmware, designed to MAX7912 matrix control
- Hackable: Open source hardware and firmware, Displays information read via UART

## Required Parts:
- Wemos D1 Mini: http://got.by/40d3u7 
- Dot Matrix Module MAX7219: http://got.by/40da6v 
- BME280 Digital Sensor (Temperature, Humidity, Barometric Pressure) 5V: http://got.by/40d52x 
- TTP223B digital touch capacitive  sensor: http://got.by/40d6kz
- DS3231 AT24C32 IIC Module Precision Clock http://got.by/42k10g
- Active Buzzer http://got.by/42k1sg
- Micro USB Cable: http://got.by/40dbf7 
Note: Using the links provided here help to support these types of projects. Thank you for the support.
**You can purchase a PCB with soldered elements and connectors for connecting the indicator and sensors, or just a PCB and a set of elements for installation. https://diy.led-lightwell.eu/product/lw-multifunctional-clock-kit/

## Schematics / Assembly
| Component  | Pins  |  Wemos D1 Mini |
| ------------ | ------------ | ------------ |
| **Dot Matrix Module MAX7219**  |  CS -->|D0 (GPIO16)|
||CLK -->|D5 (GPIO14)|
||DIN -->|D7 (GPIO13)|
||+5V -->||
||GND --> |   |
|**DS3231**|SCL -->|D1 (GPIO5)|
||SDA -->|D2 (GPIO4)|
||+3V||
||GND||
|**BME280**|SCL -->|D1 (GPIO5)|
||SDA -->|D2 (GPIO4)|
||+5V||
||GND||
|**Buzzer (active)**|+ -->|D8 (GPIO15)|
||GND||
|**TTP223B digital touch capacitive  sensor**|Dout -->|D6 (GPIO12)|
||+5V||
||GND||
|**I2C**|CS|D0 (GPIO16)|
||CLK|D5 (GPIO14)|
|**UART**|Tx|TX (GPIO1)|
||Rx|RX (GPIO3)|

1. Solder the elements on the printed circuit board according to the circuit diagram, instructions and markings placed on the printed circuit board.
2. Connect the Matrix MAX7219 indicator modules, BME280, Buzzer and TTP223B digital touch capacitive sensor using soldering or connectors.
3. Fasten the circuit board to the back of the Matrix MAX7219 LED Display Modules using M3 screws and plastic washers.
4. If you use more than four MAX7219 modules, ALWAYS connect an external 5V power supply with a capacity of 330 mA per each 8x8 module.
5. To download the sketch and files, connect the device to the computer via USB cable.

## Compiling and Loading to Wemos D1 / Installation

It is recommended to use Arduino IDE. You will need to configure Arduino IDE to work with the Wemos board and USB port and install the required USB drivers.
1. Install the Arduino IDE
2. Install the CH340G driver
3.	In the preferences dialog of the Arduino IDE, add http://arduino.esp8266.com/stable/package_esp8266com_index.json to the Additional Boards Manager URLs
4.	Open Boards Manager (under Tools), search for and install the latest version of esp8266.
5. Install the Arduino ESP8266 filesystem uploader plugin (requires restart of IDE)
6. Load and install used libraries 
7. Connect your D1 mini to the computer using a micro USB cable
8. In Tools > Flash Size: select 4M (1M SPIFFS) -- this project requires SPIFFS for saving and reading configuration settings.
9. Select the Port from the tools menu
10. Under Tools, select "LOLIN(WEMOS) D1 R2 & mini" as the board
11. Select Tools > CPU frequency: 80MHz, Flash size: 4M, Debug port: Disabled, Debug level: None, Upload speed: 921600
12. Open LWClockV1.0.ino
13. Sketch > Upload
14. Upload the sketch data files (the data directory in the sketch folder) using Tools > ESP8266 Sketch Data Upload.

## Loading Supporting Library Files in Arduino
Use the Arduino guide for details on how to installing and manage libraries https://www.arduino.cc/en/Guide/Libraries 
The following packages and libraries are used (download and install):
- ArduinoJson by Benoit Blanchon (version 6.13.0)
- TimeLib by Paul Stoffregen (version 1.5)
- MD_Parola by majicDesigns (version 3.2.0)
- MD_MAX72XX by majicDesigns (version 3.2.1)
- MD_MAXPanel by majicDesigns (version 1.2.3)
- PubSubClient by Nick O'Leary (version 2.7)
- RTClib by Adafruit  (version 1.3.3)
- Adafruit Unified Sensor by Adafruit (version 1.0.3) (for DHT sensor only)
- DHT sensor library by Adafruit (version 1.3.8) (for DHT sensor only)
- BlueDot BME280 Library by BlueDot (version 1.0.9)

Note: There could be some Issues if using different versions of the libraries.

## Initial Configuration
Starting with LW-Clock editing the Config.h file is optional. SSID and password for Wi-Fi, all API Keys are managed in the Web Interface. It is not required to edit the Config.h file before loading and running the code.

Open Weather Map free API key: http://openweathermap.org/  -- this is used to get weather data.
LW-Clock version 1.0 supports 4 and more Dot Matrix Module MAX7219-- configure in the config.h file.
**NOTE!!! If you use more than 4 modules you must connect an external power supply with a capacity of 330 mA per each 8x8 module!**
NOTE: The settings in the Config.h are the default settings for the first loading. After loading you can change the settings via the Web Interface. If you want to change settings again in the Config.h, you will need to erase the file system on the Wemos or use the “Reset Settings” option in the Web Interface.
During the first time run, Wemos D1 mini will try to connect to your Wi-Fi and fail (because it doesn't have any previously saved Wi-Fi credentials). This will cause it to start up an access point, which serves up a captive configuration portal.
You can connect to this access point to select and enter credentials for your network. Save configuration and restart device. (Wemos  D1 mini will restart and connect to your Wi-Fi network)


## Web Interface
All clock management is carried out using a web browser.  On first power-up, LW-Clock will serve a hotspot called LW-Clock. For clock adjustment and manipulation open a webpage with the 192.168.4.1 address. Within this hotspot you can manually override the time and date, set text messages for display, set timecodes of messages output  and update software.

For Wi-Fi network connection please input its SSID and password.  After successful connection LW-Clock will begin to receive and transmit information over the Internet. NTP servers are used to get accurate time. To get the current weather and forecast use the service https://openweathermap.org (you need to register and get an API key). To transmit temperature, humidity and barometric pressure data you can use the MQTT server https://www.cloudmqtt.com/ and the server https://thingspeak.com. You can also transmit information for display on the clock in the form of a creeping line through the MQTT server.

## Three types of case material 
We designed three types of the clock case, which you can choose to give a device a complete and stylish look.
First variant is made of black polished acryl, which fits perfectly into modern apartment or office.
Second variant is made of woodworking industry waste and comes as a retro-style. Different colors and finishes can give a device a unique look which fits into any design of the apartment or office.
You can order both assembling clock kit and finished case, ready for coloring or other treatment.
Third variant is made of filaments for 3D-printers (ABS, PETG, PLA etc.). You can make it yourself using a 3D printer and blueprints.
### Enclosure 3D Model
https://a360.co/2XeQH2o
https://a360.co/2HCSG9u
https://a360.co/33tJY6v

You can download plywood and acryl blueprints for CNC laser platemaker here https://github.com/Lightwell-bg/LWClock-cases

3D Printed Case https://www.thingiverse.com/thing