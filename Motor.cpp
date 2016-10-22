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

// R O T A R Y   E N C O D E R
/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */

#define R_START 0x0

#ifdef HALF_STEP
// Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  // R_START (00)
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif



Motor::Motor()
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
  // Encoder
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  #ifdef ENABLE_PULLUPS
    digitalWrite(encoderPinA, HIGH);
    digitalWrite(encoderPinB, HIGH);
  #endif
  // Initialise state.
  state = R_START;
}

Motor::Motor(int _motorPinA, int _motorPinB, int _speedPin, int _encoderPinA, int _encoderPinB)
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
  // Encoder
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  #ifdef ENABLE_PULLUPS
    digitalWrite(encoderPinA, HIGH);
    digitalWrite(encoderPinB, HIGH);
  #endif
  // Initialise state.
  state = R_START;

  Serial.begin(9600);
  Serial.print(encoderPinA);Serial.print('\t');
  Serial.println(encoderPinB);
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


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
//blocking
void Motor::advance(int _steps){
  int n = 0;
  run();
  while(n <= _steps){
    if(process()) n++;
  }
  // else{
  //
  // }
  stop();

}
// digitalReadFast()
unsigned char Motor::process() {
  // Grab state of input pins.
  unsigned char pinstate = (digitalReadFast(encoderPinB) << 1) | digitalReadFast(encoderPinA);
  // Determine new state from the pins and state table.
  state = ttable[state & 0xf][pinstate];
  // Return emit bits, ie the generated event.
  //   Serial.println(_dir == DIR_CW ? "Right" : "Left");
  return state & 0x30;
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
