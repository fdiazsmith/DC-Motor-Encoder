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

Motor::Motor() : r(3,4)
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

  dir = 0;

}
Motor::Motor(int _motorPinA, int _motorPinB, int _speedPin, int _encoderPinA, int _encoderPinB) : r(_encoderPinA,_encoderPinA)
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

}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

int Motor::getDir(){
  int _dir = r.process();
  if ( _dir ) {
    return _dir == DIR_CW ? 1 : -1 ;
  }
  else{
    return 0;
  }
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
