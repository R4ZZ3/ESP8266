#include <SoftwareSerial.h>
SoftwareSerial esp(8,9); // RX, TX 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  // enable software serial
  esp.begin(9600);
  esp.println("AT+RST");
  delay(5000);
  esp.println("AT+GMR");
  esp.println("AT+CWJAP="
  // initialize the digital pin as an output.
  pinMode(2, OUTPUT);    // Moottori, suunta 1
  pinMode(3, OUTPUT);    // Moottori, suunta 2  
  pinMode(4, OUTPUT);    // Moottori, päällä/ei päällä
}
int i = 0;
int a = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (a == 0) {
    for (i = 0; i < 75; i++)
         {
            char c = esp.read();
            Serial.print(c);
              }
  digitalWrite(4, HIGH); 
  digitalWrite(3, HIGH); 
  delay(15000);
  digitalWrite(4, LOW);
  delay(10000);
  }

  a = 1;

}
