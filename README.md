# WiFi-Weather-Station

**Things Needed:**
<pre>
  1.  Arduino UNO
  2.  ESP8266 ESP-01 WiFi Module
  3.  MQ-135 Gas sensor
  4.  DHT11
  5.  MQ-3 Alchohol Sensor
  6.  Thingspeak accout
  7.  A 2.4GHz or 5GHz Wi-Fi network
  8.  USB Cable
  9.  Arduino IDE
</pre>

__________________________________________________________________________

**Steps:**
<pre>
  Step 1: Create an Thingspeak account.
  Step 2: Create a new channel with 4 fields with the name of your choice. Do not change the 'field1/2/3/4'.
  Step 3: Copy the 'Write Key' and and paste it in the 'Key' variable.
  Step 4: Replace 'SSID' and 'PASS' with your own WiFi network credentials.
  Step 5: Install the necessary libraries.
  Step 5: Connect the USB cable to the Arduino and upload the code.
  Step 6: Detach the USB cable.

  NOTE: Please set the Wi-Fi Module Baud rate to 9600 using:
</pre>
<code>AT+UART=9600,8,1,0,0;</code>
_________________________________________________________________________________

**Hardware Connections:**
<pre>
  DHT11:
  1.  Data = 6
  2.  GND = GND
  3.  VCC = 5V
  --------------------
  MQ 135: 
  1.  Data = A1
  2.  VCC = IOREF
  3.  GND = GND
  --------------------
  MQ3:
  1.  Data: A0
  2.  VCC: IOREF
  3.  GND = GND
  --------------------
  ESP8266 ESP-01:
  1.  VCC: 3.3V
  2.  GND: GND
  3.  Enable: 3.3V
  4.  RX: 3
  5.  TX: 4
  --------------------
</pre>
__________________________________________________________________________

**Debugging:**
<pre>
  The arduino sends data about the tasks executed with or without errors on the Serial Monitor with 9600 baud.
</pre>
