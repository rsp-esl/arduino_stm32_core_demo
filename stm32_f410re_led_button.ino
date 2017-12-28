////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
/  - LED Toggle When Pressing Push Button (Use polling method)
// - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-28
////////////////////////////////////////////////////////////////////////////

#define LED_PIN       PA5   // or D13 pin 
#define USER_BTN_PIN  PC13  // user button pin 

int state = 0; // used for output (LED)
int cnt = 0;
char sbuf[64];

void setup() {
  pinMode( LED_PIN, OUTPUT ); // configure LED_PIN as output
  pinMode( USER_BTN_PIN, INPUT ); // configure USER_BTN_PIN as input
  digitalWrite( LED_PIN, state ); // update the output
  Serial.begin( 115200 );
  Serial.println( "\n\n\nArduino-STM32 Programming..." );  
}

void loop() {
  if ( digitalRead(USER_BTN_PIN) == LOW ) { // if the button is pressed.
     delay(50);
     state ^= 1;                     // toggle the state
     cnt++;                          // increment the counter
     digitalWrite( LED_PIN, state ); // update the output
     sprintf( sbuf, "LED state: %d, count: %d", state, cnt );
     Serial.println( sbuf );
     Serial.flush();
     // wait until the button is released
     while ( digitalRead(USER_BTN_PIN) == LOW ) { delay(5); } 
  }
  delay(10);
}
////////////////////////////////////////////////////////////////////////////
