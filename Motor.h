/*
  Motor.h - Motor library for Wiring - description
  Fernando Diaz Smith 2016. Free for everybody.
*/

// ensure this library description is only included once
#ifndef Motor_h
#define Motor_h

// include types & constants of Wiring core API
// #include "WConstants.h" // this crashes platformIO
#include <Arduino.h>

// library interface description
class Motor
{
  // user-accessible "public" interface
  public:
    Motor(int);
    void doSomething(void);

  // library-accessible "private" interface
  private:
    int value;
    void doSomethingSecret(void);
};

#endif
