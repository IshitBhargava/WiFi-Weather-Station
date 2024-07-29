#include <SoftwareSerial.h>     // Including the SoftwareSerial library for ESP8266 communication
#include <dht.h>                // Including the DHT sensor library
dht DHT11;                      // Initializing the DHT11 object
String temp;                   // String to store temperature
String humid;                  // String to store humidity
SoftwareSerial  esp8266(3,4);  // Creating a SoftwareSerial object for ESP8266 communication on pins 3 and 4
String PASS = "REPLACE WITH YOUR PASSWORD";  // WiFi SSID
String SSID = "REPLACE WITH YOUR SSID";     // WiFi password
String key = "REPLACE WITH YOUR WRITE API KEY";
// Function to send AT commands to ESP8266
String sendAT(String command, const int timeout)
{
  String response = "";                      // Variable to store ESP8266 response
  esp8266.print(command);                   // Sending the command to ESP8266
  long int time = millis();                // Recording current time
  while ( (time + timeout) > millis())    // Waiting for response within timeout
  {
    while (esp8266.available())          // Checking if ESP8266 data available
    {
      char c = esp8266.read();          // Reading character from ESP8266
      response += c;                   // Appending character to response string
    }
  }
  Serial.print(response);           // Printing response to serial monitor
  return response;                  // Returning response string
}

String intToString(int num) {
  return String(num);
}

void setup() {
  Serial.begin(9600);                  // Initializing serial communication
  esp8266.begin(9600);                 // Initializing ESP8266 communication
  Serial.println("Weather Monitor");  // Printing message to serial monitor
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  sendAT("AT+RST\r\n", 2000);         // Reset the ESP8266
  sendAT("AT\r\n",1000);              // Checking ESP8266 response
  sendAT("AT+CWMODE=1\r\n", 1000);   // Setting station mode operation
  sendAT("AT+CWJAP=\"" +SSID+ "\",\""+PASS+"\"\r\n", 5000);  // Connecting to WiFi
  sendAT("AT+CIFSR\r\n", 1000);     // Getting ESP8266 IP address
  sendAT("AT+CIPMUX=0\r\n",2000);  // Configuring ESP8266 for single connection mode
}

void loop() {
  int tempdata = DHT11.read11(6);     // Reading temperature and humidity data from DHT11 sensor
  int gas0 = analogRead(A0);
  int soil0 = analogRead(A1);
  String gas = String(gas0);
  String soil = String(soil0);
  intToString(soil0);
  Serial.print("Temperature =");      // Printing temperature label
  Serial.print(DHT11.temperature);    // Printing temperature value
  Serial.print("\t");                 // Printing tab
  Serial.print("Humidity =");         // Printing humidity label
  Serial.println(DHT11.humidity);    // Printing humidity value
  temp=DHT11.temperature;            // Storing temperature value in string
  humid=DHT11.humidity;              // Storing humidity value in string
  updateTS(temp,humid,gas,soil);             // Updating ThingSpeak with temperature and humidity data
  delay(3000);                      // Delay for stability
}

void updateTS(String T, String H, String G, String S)
{
  Serial.println("");                                                 // Printing empty line
  sendAT("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n",1000);  // Establishing TCP connection with ThingSpeak
  delay(2000);                                                    // Delay for stability
  String cmdlen;                                                   // String to store command length
  String cmd = "GET /update?key="+key+"&field1="+T+"&field2="+H+"&field3="+G+"&field4="+S+"\r\n";  // Building GET request URL with temperature and humidity data
  cmdlen=cmd.length();                                              // Calculating command length
  sendAT("AT+CIPSEND="+cmdlen+"\r\n",2000);                        // Sending command length to ESP8266
  esp8266.print(cmd);                                              // Sending GET request to ThingSpeak
  Serial.println("");                                             // Printing empty line
  sendAT("AT+CIPCLOSE\r\n",2000);                               // Closing TCP connection
  Serial.println("");                                           // Printing empty line
  delay(10000);                                                  // Delay for stability
}
