#include <Wire.h> // tämä alkuun
#include <SoftwareSerial.h> // tämä alkuun

char pass[12] = "\"****\"";   /// nämä alkuun ennen setup
char ssid[12] = "\"******\"";     // alkuun ennen setuppia

SoftwareSerial esp8266(2,3); // RX, TX //// määrittellään Arduinon pinnit joihin ESP8266:n RX ja TX tulee kiinni


/// Nämä ajetaan Setupissa
  // enable software serial
  esp8266.begin(9600);


/// Tämä yhdistää ESP8266:n 
// Yhteinen maa esp8266+arduino
// tarkista kytkennät
// ESP8266:lle oma virtalähde(3,3V)
// katso että ESP8266:ssa palaa valo
// muista avata yhteys
// muista että ssid ja pass on oikein

  // connect ESP8266
boolean yhdistysESP8266(){
esp8266.println("AT+CWMODE=1");
    delay(2000);
String cmd="AT+CWJAP=\"";
cmd+=SSID;
cmd+="\",\"";;
cmd+=PASS;
cmd+="\"";
esp8266.println(cmd);
delay(5000);
}
}
