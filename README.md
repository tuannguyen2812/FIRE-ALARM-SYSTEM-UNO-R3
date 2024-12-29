<h1 align="center">FIRE ALARM SYSTEM</h1>
<h2 align="center">International School - Vietnam National University</h2>
<h3 align="center">Course: Computers and Seripheral Devices</h3>

<h3 align="left">I. Introduction</h3>
A fire alarm system is designed as a combination of CCS-811, MQ-135, DHT11, and Flame sensors that detect fire indicators such as smoke, gas, and temperature changes. This system uses an Arduino UNO microcontroller for data acquisition and processing, displaying outputs on a 16x02 LCD screen. The CCS-811 and MQ-135 sensors detect smoke and harmful gases, DHT11 measures temperature and humidity, and the Flame sensor detects fire presence. Our results demonstrate the effectiveness of using these sensors for comprehensive fire detection. The integration of multiple sensors enhances system accuracy, particularly in high-risk environments.
  
<h3 align="left">II. Software Design</h3>
1. Principle diagram<br>
<a href="https://drive.google.com/uc?export=view&id=1Ooq0dr7KgEugzozxIUGMMsbSh2L9RBt3"><img src="https://drive.google.com/uc?export=view&id=1Ooq0dr7KgEugzozxIUGMMsbSh2L9RBt3" style="width: 500px; max-width: 100%; height: auto" title="Click for the larger version."/></a><br>
2. Configuration<br>
- MQ-135 (Gas Sensor)<br>
Analog Pin (A0): The MQ-135 sensor measures the concentration of various gases
like CO₂, NH₃, and NO. The analog signal output corresponds to the gas concentration
level and is connected to an analog input pin on the microcontroller for digital
conversion and processing.<br>
5V and GND: These provide power and ground to the sensor, enabling it to
operate.<br>
- DHT11 (Temperature and Humidity Sensor)<br>
Digital Pin (D2): The DHT11 transmits temperature and humidity data through a
digital signal. It connects to a digital input pin on the microcontroller, requiring only
one data wire for transmitting temperature and humidity information.<br>
- CCS811 (Gas Sensor)<br>
I2C Communication (SCL and SDA): The CCS811 sensor communicates with the
microcontroller over the I2C interface, using the same SCL (Clock) and SDA (Data)
pins shared by other I2C devices. This sensor measures eCO₂ (equivalent CO₂) levels
in parts per million (ppm) and TVOC (Total Volatile Organic Compounds) levels in
parts per billion (ppb).<br>
Power (1.8V to 3.6V) and GND: This sensor operates at a lower voltage range
than the MQ-135, with 3.3V being the most common.<br>
Gas Detection: The CCS811 offers real-time monitoring of air quality, specifically
measuring indoor air pollutants like CO₂ and TVOCs, making it an excellent
complement to the MQ-135 sensor.<br>
- Flame Sensor35<br>
Digital Pin (D3): The flame sensor detects infrared light emitted by flames and
outputs a digital signal, indicating the presence of fire. This sensor’s digital output
connects to a digital input pin on the microcontroller.<br>
- LCD Display via I2C<br>
SCL (Clock) and SDA (Data) Pins: These pins handle I2C communication, with
SCL for the clock signal and SDA for data transfer. The LCD’s I2C module reduces
the number of required connection pins to just two, simplifying the setup.
I2C Protocol: The I2C protocol allows multiple devices, like the LCD and
CCS811, to communicate over the same two wires, reducing circuit complexity.<br>
- Status LEDs (Red)<br>
Digital Pins (D4): These LEDs provide status indicators. The red LED can light
up for high gas concentration or flame detection, while the green LED shows normal
conditions.<br>
- Buzzer<br>
Digital Pin (D7): The buzzer sounds an audible alarm during hazardous
conditions, such as high gas levels or flame detection. The microcontroller can control
the buzzer’s on/off states for effective alerting.<br>
3. Result: <br>
<a href="https://drive.google.com/uc?export=view&id=1AqBP49oPx8ktcITM_EOvJU8CYTXIsJmy"><img src="https://drive.google.com/uc?export=view&id=1AqBP49oPx8ktcITM_EOvJU8CYTXIsJmy" style="width: 500px; max-width: 100%; height: auto" title="Click for the larger version."/></a><br>
<h3 align="left">III. Contribution</h3>
Tran Van Tuong - Leader<br>
Duong Ton Dung - Member<br>
Nguyen Luu Anh Tuan - Member<br>
