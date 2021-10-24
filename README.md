# Final-Year-Project
Gestate-Tracker app - Final year project - Group 6 - ASIET - 2017-21 batch (Akanksha S,Arathy S Kumar,Athira S Kumar)
The main objective of the project is to help expectant mothers, especially the ones in rural areas, by providing cost-effective home pregnancy care. It aims in designing an Android mobile application that can display the fetal heart rate value. The hardware part is a combination of Heart Sensors, Pressure sensors and temperature sensor since the heart rate is observed depending on the parameters Pressure and Temperature. The digital value will be available in a display device. The project is assumed to be cost effective and easily available to common people as well. The hardware components in the project will be of good quality producing accurate results. Also, the whole system can be produced as a small handy product.

The project aims to design an web application that focuses on displaying the parameters like Temperature, Pulse Rate, Systolic BP, Diastolic BP, Oxygen saturation, Hemoglobin, which helps in determining the condition of pregnant women. This can also be used by common people to detect their health conditions or monitor their body parameters. It also aims to implement hardware that can measure the maternal heart rate (MHR) activity and find out if the mother is under stress or not. The output will be on a real-time display. The system enables it to ensure that the heart rate of the mother is maintained.
The user is assumed to be the maternal or for demonstration purpose of any person who has a smartphone through which the entire system can be integrated through a Wi-fi module.

The hardware setup consists of an Arduino UNO/Nano board, MAX30102 sensor, LED display, and LED. The benefit of using this sensor is that it is integrated pulse oximetry and a heart-rate monitor module. It consists of internal LEDs, photodetectors, optical elements, and low-noise electronics with ambient light rejection.
Once the user opens the web application, the corresponding values of the following listed below will be displayed on the screen. The following values are displayed: User ID, Date & Time, Temperature, Pulse Rate, Systolic BP, Diastolic BP, Oxygen saturation, Haemoglobin. Further, this system can be extended using ECG sensors to detect the ECG of the user and monitor their health condition without any medical assistance.

IMPLEMENTATION

The system is implemented as follows: Place the finger on the sensor to detect values. Sensor esteems are gathered by Arduino and processed. We interface MAX30102: beat oximetry and pulse screen module with Arduino UNO board, and afterward make a task for estimating BPM utilizing this module + OLED show and a Buzzer.
Highly trained athletes may have a resting heart rate below 60 bpm, sometimes reaching 40 bpm. The resting heart rate can vary within this normal range. The SpO2 is the Oxygen saturation level and it measures the amount of oxygen being carried in your blood, as a percentage. According to sources, the SpO2 level for a common person is above 95%. The MAX30102 can be found in various modules SpO2 subsystem of the MAX30102 contains encompassing light scratch-off (ALC), a constant time sigma-delta ADC. The MAX30102 has an on-chip temperature sensor for adjusting the temperature reliance of the SpO2 subsystem. The temperature sensor has a characteristic goal of 0.0625°C. When you put your finger, resist the urge to panic for some time, until you begin hearing the Buzzer's "Blares" synchronized with your heartbeats or the OLED activity is synchronized with it, and afterward, you can peruse the right BPM.


HARDWARE CONNECTIONS

Power supply -regulator - 5V - Arduino and LCD runs on this voltage
● Adapter connected to DC Jack
● AMS117 - 3.3 V regulator - Sensor and Wifi-module uses 3.3V
Input of the regulator is 5V. 
● Node MCU - used for connecting sensors using I²C communication.Its ESP_RXD and TX pin are connected to Arduino to transfer data.It uses serial communication. 
● Data passed to the arduino and LCD is connected. 
● LCD is an indicator to ensure connections and display error if any LCD is connected to A4 and A5 pins of Arduino.



SOFTWARE


The program is written in ‘C++’ language. It is compiled and programmed (uploaded) into the target device/board using Arduino integrated development environment (IDE). Arduino IDE is a cross-platform application (for Windows, macOS, Linux) that is written in the programming language
Java. It is used to write and upload programs to Arduino compatible boards, but also, with the help of 3rd party cores, other vendor development boards. In our system design software two source code i.e
sketches in terms of Arduino need to develop one is for the main Microcontroller unit that is Arduino nano board and other is for the Wi-Fi module called Node MCU.

SOFTWARE TOOLS USED

ARDUINO UNO
XAMPP

