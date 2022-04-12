#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 7);  // RX, TX
String command = "";             // Stores response of bluetooth device
Servo myservo;
int current = 96;
void setup() {
  //Setup Channel A

  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(2);
  myservo.write(current);

  pinMode(13, OUTPUT);  //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);   //Initiates Brake Channel A pin
}

void loop() {

  int value = (int)mySerial.read();  //mySerial.readStringUntil('#');

  if (value != -1) {
    Serial.println(value);
    if (value == 52) {
      forward();
    } else if (value == 50){
      back();
    } else if (value == 49){
      stop();
    } else {
        if (value == 87) {
          current = 96;

        } else if (value == 83) {  //left
          current = current - 2;
        } else if (value == 78) {  //right
          current = current + 2;
        }
        myservo.write(current);
    }
  }
  delay(100);
}

void back() {
  //forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel A
  analogWrite(11, 123);   //Spins the motor on Channel A at full speed
}

void stop() {
  //forward @ full speed
  digitalWrite(8, HIGH); //Eengage the Brake for Channel 
}

void forward() {
  //forward @ full speed
  digitalWrite(13, LOW); //Establishes forward direction of Channel A
  digitalWrite(8, LOW);   //Disengage the Brake for Channel A
  analogWrite(11, 123);   //Spins the motor on Channel A at full speed
}
