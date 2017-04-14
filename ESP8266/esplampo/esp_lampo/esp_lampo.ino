#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "rt";
const char* password = "R4ZZ392!";
float paine = 0;     // for pressure

// LED 
int ledPin = 13;


// replace with your channel's thingspeak API key
String apiKey = "5R39CPOEIOZND7GW";

// connect 2 to TX of Serial USB
// connect 3 to RX of serial USB
SoftwareSerial ser(3,2); // RX, TX
Adafruit_BMP085 bmp;

// this runs once
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);    
  

  // enable debug serial
  Serial.begin(9600); 
  delay(200);
  // enable software serial
  ser.begin(9600);
  delay(200);
  
  //aloita bmp sensorin käyttö
bmp.begin(9600);
delay(200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
}

// the loop 
void loop() {
  
  // blink LED on board
  digitalWrite(ledPin, HIGH);  
  delay(500);              
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  
  pressure();
  esp_8266();
}

void pressure()
{
paine=bmp.readPressure();
Serial.print(paine);
Serial.println(" Pa");
}

void esp_8266()
{
 // convert to string
  char buf[32];
  String strPressure = dtostrf(paine, 4, 1, buf);
  Serial.print(strPressure);
  Serial.println(" Pa");
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strPressure);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
    
  // thingspeak needs 15 sec delay between updates
  delay(16000);  
}

