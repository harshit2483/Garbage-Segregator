
# Garbage Segregator

This project utilizes an ESP8266 microcontroller to create a garbage segregator system capable of detecting and segregating wet and dry waste. It employs various sensors to detect the type of waste and actuates a servo motor to open the corresponding bin accordingly.



## Features

- IR Sensor: Detects the presence of garbage on the segregator plate.
- Rain Sensor: Determines whether the detected waste is wet or dry.
- Ultrasonic Sensor: Ensures the bins are not overfilled by detecting the distance of the waste from the sensor.
- Web Interface: Provides a simple web interface for monitoring the system and receiving notifications.


## Components
- ESP8266 
- microcontroller
- IR sensor
- Rain sensor
- Ultrasonic sensor
- Servo motor

## Installation

1. Install the required libraries for ESP8266, Servo, and WebServer.
2. Connect the sensors and servo motor to the specified pins on the ESP8266.
3. Upload the code to the ESP8266 using the Arduino IDE or another compatible IDE.
4. Configure the WiFi SSID and password in the code to connect the ESP8266 to your network.
    
## Usage
1. Power on the system and ensure it is connected to the WiFi network.
2. Place garbage on the segregator plate.
3. The system will detect the type of waste (wet or dry) and open the corresponding bin.
4. Access the web interface to monitor the system status and receive notifications.
## Authors

- [@Harshit Sharma](https://github.com/harshit2483)
- [@Kavya Chaurasia](https://github.com/kavyac31)
- [@Shivanshu Gupta](https://github.com/kabir9999)


## Contributors
Contributions to improve the project are welcome! You can contribute by:

Adding new features or sensors
Improving code efficiency and readability
Fixing bugs or issues