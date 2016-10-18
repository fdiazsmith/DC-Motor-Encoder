#include <Arduino.h>
//  L I B R A R I E S
#include <Motor.h> //work in progress still

//constants
#define m1LeadA 2
#define m1LeadB 3
#define m1Speed 80

#define m1EncoderA 12
#define m1EncoderB 13

#define m1SpeedPin 9

//
Motor m1 = Motor(m1LeadA,m1LeadB, m1SpeedPin, m1EncoderA,m1EncoderB);

void setup() {  // Setup runs once per reset
  // initialize serial communication @ 9600 baud:
  Serial.begin(9600);
  Serial.println("ready");
  // m1.setSpeed(120);

};

void loop() {

  unsigned char _dir = m1.getDir();//().process();
  if (_dir) {
    Serial.print("m"); Serial.print("\t");
    Serial.print(digitalRead(m1EncoderB)); Serial.print("\t");
    Serial.print(digitalRead(m1EncoderA)); Serial.print("\t");
    Serial.println(_dir == DIR_CW ? "Right" : "Left");
  }
  m1.run();
  delay(2000);
  m1.stop();
  delay(2000);
  m1.run(-1);
  delay(2000);

}
