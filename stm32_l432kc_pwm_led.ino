////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
// - PWM-based LED dimming
// - Tested with Nucleo L432KC Board
// Author: Rawat S.
// Date: 2017-12-29
////////////////////////////////////////////////////////////////////////////

#define PWM_LED_PIN   PB3  // PB_3 or D13 pin 
#define DELAY_MS      10

uint8_t value = 0; // used to store the PWM duty cycle between 0..255
int pm = 1; // 1 or -1

void setup() {
  pinMode( PWM_LED_PIN, OUTPUT ); // configure PWM_LED_PIN as output
  analogWrite( PWM_LED_PIN, value );
}

void loop() {
  if ( value == 255 && pm == 1 ) {
    pm = -1; // decrement
  } else if ( value == 0 && pm == -1 ) {
    pm = 1;  // increment
  }
  value += pm;
  analogWrite( PWM_LED_PIN, value ); 
  delay( DELAY_MS );
}
////////////////////////////////////////////////////////////////////////////

