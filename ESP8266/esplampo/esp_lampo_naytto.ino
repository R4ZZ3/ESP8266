#include "DHT.h"
#define DHTPIN 8     //digital pin
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//#include <Wire.h>

#include <LiquidCrystal.h> //näyttöpaneeli
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //paneelin alustus




#include <SoftwareSerial.h> //Software Serial is needed to interface with ESP8266 because the hardware serial 
//is being used for monitoring Serial line with computer during trouble shooting.
#define ESP8266_rxPin 6
#define ESP8266_txPin 7
SoftwareSerial ESP8266(ESP8266_rxPin, ESP8266_txPin);// rx tx


#define IP "184.106.153.149" // thingspeak.com IP address; see their website for more detail
String GET = "GET https://api.thingspeak.com/update?api_key=**********&field"; // you channel will have unique code https://api.thingspeak.com
//String GET = "http://api.thingspeak.com/update?api_key=QR2S4RDZ4R2WA0QV&field"; // you channel will have unique code https://api.thingspeak.com
String field1="1=";
String field2="2=";


float t_=0.0,h_=0.0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin (16,2);       
  lcd.print("Terve!");   
  //Serial.begin(9600); // this is to start serial monitoring with your Arduino IDE Serial monitor.
  ESP8266.begin(9600); // this is to start serial communication with the ESP via Software Serial.
  ESP8266.println("AT+RST"); // this resets the ESP8266.
  //Serial.println("AT+RST"); // this is just echoing the command to your serial monitor so you can
  // follow what is going on - this is not really needed.
  // through out the code below I echo almost everything to the Serial monitor which you
  // you don't have to do and can eliminate from the code.
 
  delay(2000);
  dht.begin();
  
  ESP8266.println("AT");
  //Serial.println("AT");
  
  delay(5000);
  if(ESP8266.find("OK")){
      //Serial.println("OK");  
  
      //Serial.println("Connected");
  }    
}

void loop() {
  delay(12000);
  //sensors_event_t event;
  //bmp.getEvent(&event);
  char buffer[16];
  //Serial.println("in the main loop");
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  //float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float t = dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("Lampotila ");
  lcd.print(t);
  lcd.setCursor(0,1);
  lcd.print("Kosteus ");
  lcd.print(h);
  /*
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  */
  
  String temp=dtostrf(t,4,1,buffer);
  //Serial.println(temp);
  update(temp,field1,"t_");

  delay(12000);
  String humidity=dtostrf(h,4,1,buffer);
  //Serial.println(humidity);
  update(humidity,field2,"h_");
    
  
  delay(10000);
  //Serial.println("loop-de-loop");  
}

void update(String value, String field, String previous_value_var){

  //Serial.println("in the update loop"); 
  ESP8266.println("AT+RST"); // it seems that mine works better if I reset it everytime before I do CIPSTART
  //Serial.println("AT+RST");
  delay(15000);
  //ESP8266.println("AT+CWMODE=1");
  //delay(500); 
  //ESP8266.println("+++"); 
  //delay(200);
  String cmd = "AT+CIPSTART=\"TCP\",\""; //standard code. see https://github.com/espressif/esp8266_at/wiki //
  cmd += IP; // += is concatenating the previous cmd string with the content of IP
  cmd += "\",80"; // same thing here it just keep adding stuff to the cmd string content

  ESP8266.println(cmd);//type in the string in cmd into the ESP8266
  //Serial.println(cmd);
  delay(5000);
  if(ESP8266.find("OK"))
    //Serial.println("Yhteys saatu");
  if(ESP8266.find("Error")){
    //Serial.println("AT+CIPSTART Error");
    return;
  }
  cmd = GET;
  cmd += field;
  cmd += value;
  cmd += "\r\n\r\n"; // it seems that this part is important, to input enough \r\n, mine does not work if I only have one pair.
  //Serial.print("AT+CIPSEND=78\r\n");
  //Serial.println(cmd.length());
  //Serial.println(cmd);
  ESP8266.print("AT+CIPSEND=78\n"); 
  //ESP8266.println(cmd.length());

  delay(3000);
  
  if(ESP8266.find(">")){ // if ESP8266 return the > prompt back from the CIPSEND command, you are set, if not something is wrong
    cmd += "\r\n";
    ESP8266.print(cmd); //type in the GET command string and done
    //Serial.print(">");
    //Serial.println(cmd);
    previous_value_var=value;    
  }
  else
  {
   //Serial.println("AT+CIPCLOSE"); //this command somehow does not work and always return errors so I just comment it out
   ESP8266.print(cmd); //type in the GET command string and done
   //Serial.println("AT+CIPSEND error");
  }

}


