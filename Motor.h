/*
  Motor.h - Motor library for Wiring - description
  Fernando Diaz Smith 2016. Free for everybody with <3 xoxo
  ** The encoder method was pulled from  Brian Low whom in turned pulled it from Ben Buxton's (Buxtronix)

  if you want to learn how encoders work or just use the library by it self be sure to check their sites.

  Brian Low - https://github.com/brianlow/Rotary
  Buxtronics - http://www.buxtronix.net/2011/10/rotary-encoders-done-properly.html

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


#include <digitalWriteFast.h>  // library for high performance reads and writes by jrraines
                               // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                               // and http://code.google.com/p/digitalwritefast/

// Enable this to emit codes twice per step.
// #define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20

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
    void advance(int);
    unsigned char process();


  // library-accessible "private" interface
  private:

    int motorPinB;
    int motorPinA;
    int encoderPinA;
    int encoderPinB;
    int speedPin;
    int dir;
    unsigned char state;

};

#endif
