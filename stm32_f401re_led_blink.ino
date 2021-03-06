////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino: 
// - LED Blink
// - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-28
////////////////////////////////////////////////////////////////////////////

#define LED_PIN   PA5  // PA5 or D13 pin 
#define DELAY_MS  100

int state = 0; // used for output (LED)

void setup() {
  pinMode( LED_PIN, OUTPUT ); // configure LED_PIN as output
}

void loop() {
  digitalWrite( LED_PIN, state ); // update the output
  state ^= 1;          // toggle the state
  delay( DELAY_MS );   // delay approx. for 100 msec
}
////////////////////////////////////////////////////////////////////////////
