////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - Timer-based LED Toggle
//  - Tested with Nucleo L432KC Board
// Author: Rawat S.
// Date: 2017-12-29
////////////////////////////////////////////////////////////////////////////

#define LED_PIN   PB3    // PB_5 or D13 pin 
#define USE_TIM   TIM1   // specify which STM32 timer to be used

stimer_t TimeHandle;
int state = 0;

void timer_callback( stimer_t *t ) {
   state ^= 1;                     // toggle the state
   digitalWrite( LED_PIN, state ); // update the LED output
}

void setup() {
   pinMode( LED_PIN, OUTPUT );
   uint16_t freq = 100000; // freq = 10^5 Hz or period = 10 usec 
   uint16_t prescaler = getTimerClkFreq( USE_TIM )/freq - 1;
   uint16_t period = 5000 - 1;
   TimeHandle.timer = USE_TIM;
   TimerHandleInit( &TimeHandle, period /* 16-bit period */, prescaler /* 16-bit prescaler */ );
   attachIntHandle( &TimeHandle, timer_callback ); // callback every 50 msec
}

void loop() {
   delay(100); 
}
////////////////////////////////////////////////////////////////////////////

