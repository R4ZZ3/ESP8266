/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor

 This example code is in the public domain.
 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 13;

// the setup routine runs once when you press reset:
void setup() {
  // make the pushbutton's pin an input:
pinMode(13, INPUT);
pinMode(12, OUTPUT);
pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  if (buttonState = 1){
    pinMode(12, HIGH);
    delay(500);
    pinMode(11, HIGH);
    delay(500);
    pinMode(10, HIGH);
    delay(500);
    pinMode(9, HIGH);
    delay(1000);
    pinMode(9, LOW);
    delay(500);
    pinMode(10, LOW);
    delay(500);
    pinMode(11, LOW);
    delay(500);
    pinMode(12,LOW);
    delay(1000);
  }

}



