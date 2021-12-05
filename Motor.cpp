/*
  Motor.h - Motor library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// include this library's description file
#include "Motor.h"
// include description files for other libraries used (if any)
#include "HardwareSerial.h"

Motor::Motor() : r(4,5)
{
  // initialize this instance's variables
  motorPinB = 2;
  motorPinA = 3;
  encoderPinA = 4;
  encoderPinB = 5;
  speedPin =  6;
  // do whatever is required to initialize the library
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  pinMode(speedPin, OUTPUT);
  // r(4,5);
  dir = 0;

}
Motor::Motor(int _motorPinA, int _motorPinB, int _speedPin, int _encoderPinA, int _encoderPinB) : r(_encoderPinA,_eencoderPinB )
{
  // initialize this instance's variables
  motorPinA = _motorPinA;
  motorPinB = _motorPinB;
  speedPin = _speedPin;
  encoderPinA = _encoderPinA;
  encoderPinB = _encoderPinB;

  // do whatever is required to initialize the library
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  pinMode(speedPin, OUTPUT);

  Serial.begin(9600);
  Serial.print(encoderPinA);Serial.print('\t');
  Serial.println(encoderPinB);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

int Motor::getDir(){
  return r.process();
}

Rotary Motor::getEncoder(){
  return r;
}

void Motor::setSpeed(int _speed){
  speed = _speed;
}

void Motor::run(){
  //forward
  analogWrite(speedPin, speed);//Sets speed variable via PWM
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, HIGH);
}
void Motor::run(int _dir){
  switch(_dir){
    //forward
    case 1:
      analogWrite(speedPin, speed);//Sets speed variable via PWM
      digitalWrite(motorPinA, LOW);
      digitalWrite(motorPinB, HIGH);
      break;
      //reverse
    case -1:
      analogWrite(speedPin, speed);//Sets speed variable via PWM
        digitalWrite(motorPinA, HIGH);
      digitalWrite(motorPinB, LOW);
    break;
  }

}
void Motor::stop(){
  analogWrite(speedPin, 0);//Sets speed variable via PWM
  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, HIGH);
}
// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
