/*
  Motor.h - Motor library for Wiring - description
  Fernando Diaz Smith 2016. Free for everybody.
*/

// ensure this library description is only included once
#ifndef Motor_h
#define Motor_h

// include types & constants of Wiring core API
#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Rotary.h>

// library interface description
class Motor
{
  // user-accessible "public" interface
  public:
    Motor(void);
    Motor(int, int, int, int, int);

    int value;
    int speed;
    int acceleration;
    int getDir(void);

    void doSomething(void);


  // library-accessible "private" interface
  private:
    boolean direction;
    int motorPinB;
    int motorPinA;
    int encoderPinA;
    int encoderPinB;
    int speedPin;
    // unsigned char processType;
    Rotary r(int, int);
    // Rotary
    void doSomethingSecret(void);
};

#endif
