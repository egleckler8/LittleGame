#include "LedControl.h"

// Led control stuff
LedControl lc = LedControl(12, 10, 11, 1);
const int delaytime1 = 50;
const int delaytime2 = 100;

// Joystick control stuff
const int x_pin = 0; // analog pin 0
const int y_pin = 1; // analong pin 1
//const int sw_pin = 8;
const int threshold = 10;


void setup() {
  
  // Set up joystick switch input pin
  //pinMode(sw_pin, INPUT);

  // Set up led display
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
} // END OF FUNCTION setup()

// initial cursor pos starting at (1, 1)
int x_pos = 0;
byte y_pos = B10000000;


void updateCursor() {
  // This loop updates the graphics on the led grid

  // Do this first obviously
  lc.clearDisplay(0);

  // Then update it based on our pos
  for(int row = 0; row < 8; row++) {
    // If the xposition is the same as the row we're updating
    if (x_pos == row) {
      lc.setRow(0, x_pos, y_pos);
    }
  }

} // END OF FUNCTION updateGraphics()


void updatePos() {
  // Update the position of our blinky dude!

  // First update x_pos
  if (analogRead(x_pin) > (512 + threshold) && x_pos < 7) { // can't send it to row 8!!
    x_pos++;
  } else if (analogRead(x_pin) < (51 - threshold) && x_pos > 0) { // can't send it to row 0!!
    x_pos--;
  } else {} // the joystick will be in the middle... no motion in the y

  
  // Update y_pos
  if (analogRead(y_pin) > (512 + threshold) && y_pos > B00000001) { // can't send it to column 9! which is B00000000 1 NONEXISTENT!
    y_pos /= 2; // y is a byte!
  } else if (analogRead(y_pin) < (512 - threshold) && y_pos < B1000001) { // can't send it to column 0!! which is B1 00000000 NONEXIESTENT
    y_pos *= 2; // y is a byte!
  } else {} // the joystick will be in the middle... no motion in the y

} //  END OF FUNCTION updatePos()


void loop() {
  updatePos();
  updateCursor();
  delay(delaytime1);
  

} // END OF FUNCTION loop()
