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
    int speed = 255;
    void setSpeed(int);
    int acceleration;
    int getDir(void);

    void run(void);
    void run(int);
    void stop();

    Rotary getEncoder();

  // library-accessible "private" interface
  private:

    int motorPinB;
    int motorPinA;
    int encoderPinA;
    int encoderPinB;
    int speedPin;
    int dir;
    Rotary r;

};

#endif
