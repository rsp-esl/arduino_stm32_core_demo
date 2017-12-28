////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
/  - LED Toggle When Pressing Push Button (Use External Interrupt)
// - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-28
////////////////////////////////////////////////////////////////////////////

#define LED_PIN       PA5   // or D13 pin 
#define USER_BTN_PIN  PC13  // user button pin 

volatile int state = 0; // used for output (LED)
volatile int cnt = 0;
volatile bool state_changed = false;
char sbuf[64];

#define interrupts()    __enable_irq() 
#define noInterrupts()  __disable_irq()

void irq_handler( ) {
  noInterrupts();
  //detachInterrupt( USER_BTN_PIN );
  state ^= 1;        // toggle the state
  cnt++;             // increment the counter
  state_changed = true;
  //attachInterrupt( USER_BTN_PIN, irq_handler, FALLING );
  interrupts();
}

void setup() {
  pinMode( LED_PIN, OUTPUT ); // configure LED_PIN as output
  pinMode( USER_BTN_PIN, INPUT ); // configure USER_BTN_PIN as input
  digitalWrite( LED_PIN, state ); // update the output
  Serial.begin( 115200 );
  Serial.println( "Arduino-STM32 Programming..." );  
  attachInterrupt( USER_BTN_PIN, irq_handler, FALLING );
}

void loop() {
  if ( state_changed ) { // if the button is pressed.
     state_changed = false;
     sprintf( sbuf, "LED state: %d, count: %d", state, cnt );
     Serial.println( sbuf );
     Serial.flush();
  }
  delay(10);
}
////////////////////////////////////////////////////////////////////////////
