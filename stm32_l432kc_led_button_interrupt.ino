////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
// - Toggle the LED when pressing push button (use external interrupt)
// - Tested with Nucleo L432KC Board
// Author: Rawat S.
// Date: 2017-12-29
////////////////////////////////////////////////////////////////////////////

#define LED_PIN      PB3   // PB_3 or D13 pin 
#define BTN_PIN      PB4   // PB_4 or D12 pin 

volatile int state = 0; // used for output (LED)
volatile int cnt = 0;
volatile bool state_changed = false;
char sbuf[64];

void irq_handler( ) {
  detachInterrupt( BTN_PIN );
  state ^= 1;        // toggle the state
  cnt++;             // increment the counter
  state_changed = true;
}

void setup() {
  pinMode( LED_PIN, OUTPUT ); // configure LED_PIN as output
  pinMode( BTN_PIN, INPUT_PULLUP );  // configure BTN_PIN as input
  digitalWrite( LED_PIN, state ); // update the output
  Serial.begin( 115200 );
  Serial.println( "Arduino-STM32 Programming - Nucleo L432KC..." );  
  attachInterrupt( BTN_PIN, irq_handler, FALLING );
}

void loop() {
  if ( state_changed ) { // if the button is pressed.
     state_changed = false;
     digitalWrite( LED_PIN, state );
     sprintf( sbuf, "LED state: %d, count: %d", state, cnt );
     Serial.println( sbuf );
     Serial.flush();
     attachInterrupt( BTN_PIN, irq_handler, FALLING );
  }
  delay(10);
}
////////////////////////////////////////////////////////////////////////////

