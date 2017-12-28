////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - Timer-based LED Toggle
//  - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-28
////////////////////////////////////////////////////////////////////////////

#define LED_PIN  PB4  // PB_4 or D5 pin

#define USE_TIM  TIM2   // specify which STM32 timer to be used

stimer_t TimeHandle;
int state = 0;

void timer_callback( stimer_t *t ) {
   state ^= 1;                     // toggle the state
   digitalWrite( LED_PIN, state ); // update the LED output
}

void setup() {
   pinMode( LED_PIN, OUTPUT );

   uint16_t freq = 10000; // freq = 10^4 Hz or period = 100 usec 
   uint16_t prescaler = getTimerClkFreq( USE_TIM )/freq - 1;
   uint16_t period = 1000 - 1;
   TimeHandle.timer = USE_TIM;
   TimerHandleInit( &TimeHandle, period /* 16-bit period */, prescaler /* 16-bit prescaler */ );
   attachIntHandle( &TimeHandle, timer_callback ); // callback every 100 msec
}

void loop() {
   delay(100); 
}
////////////////////////////////////////////////////////////////////////////

