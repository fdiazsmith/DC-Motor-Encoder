This is an example C++ library for Arduino 0004+, based on one created by 
Nicholas Zambetti for Wiring 0006+

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.

When installed, this library should look like:

Arduino/lib/targets/libraries/Motor              (this library's folder)
Arduino/lib/targets/libraries/Motor/Motor.cpp     (the library implementation file)
Arduino/lib/targets/libraries/Motor/Motor.h       (the library description file)
Arduino/lib/targets/libraries/Motor/keywords.txt (the syntax coloring file)
Arduino/lib/targets/libraries/Motor/examples     (the examples in the "open" menu)
Arduino/lib/targets/libraries/Motor/readme.txt   (this file)

Building
--------------------------------------------------------------------------------

After this library is installed, you just have to start the Arduino application.
You may see a few warning messages as it's built.

To use this library in a sketch, go to the Sketch | Import Library menu and
select Motor.  This will add a corresponding line to the top of your sketch:
#include <Motor.h>

To stop using this library, delete that line from your sketch.

Geeky information:
After a successful build of this library, a new file named "Motor.o" will appear
in "Arduino/lib/targets/libraries/Motor". This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. "Motor.cpp" or "Motor.h"),
then you must first 'unbuild' this library by deleting the "Motor.o" file. The
new "Motor.o" with your code will appear after the next press of "verify"

