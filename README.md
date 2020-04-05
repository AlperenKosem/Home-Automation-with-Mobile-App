# Home Automation with Mobile Application

Home automation is a network of hardware, communication, and electronic interfaces that work to integrate everyday devices with one another via the Internet. Each device has sensors and is connected through WiFi, so you can manage them from your smartphone or tablet whether you’re at home, or miles away. 

In this project, four main structures were used for making "Smart Home". 

### Four main hardware and softwares

* Database: Firebase used which provided by google
* Microcontroller: Arduino ESP8266 D1 Mini WiFi module
* Sensors and Actuators: Magnetic Door Switch, DHT11(Humidity - Temperature Sensor), Heater, Cooler(12V DC fan), Door Alarm(Buzzer), Servo Motor
* Mobile App: MIT App Inventor used which provided by MIT.


## Getting Started

You can see the pin distribution in the script of the arduino code("HomeAutomationArduino.ino")
You can open "HomeAutomationApp.aia" in the app inventor, then change the firebase setting and build for apk.

### Prerequisites

You need to implement some libraries for arduino firebase communication.

* ArduinoJson Library
* ESP8266 Core SDK
* firebase-arduino Library


