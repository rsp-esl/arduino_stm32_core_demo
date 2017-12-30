////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - Analog Reading (Input Voltage between 0V to 3.3V)
//  - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-28
////////////////////////////////////////////////////////////////////////////
#define DELAY_MS      1000

char sbuf[32];
float volt;

void setup() {
  Serial.begin( 115200 );
  analogReadResolution(12); // use 12-bit ADC resolution (instead of 10bit)
}

const int ADC_CHANNELS = 6;
int values[ ADC_CHANNELS ] = {0};

// #define USE_ARDUINO_PINS

#ifdef USE_ARDUINO_PINS
 uint8_t ADC_PINS[] = { A0, A1, A2, A3, A4, A5 }; // PA0, PA1, PA4, PB0, PC1, PC0 
#else
 uint8_t ADC_PINS[] = { PA0, PA1, PA4, PB0, PC1, PC0 };
#endif

void loop() {
  for ( int i=0; i < ADC_CHANNELS; i++ ) {
     values[i] = analogRead( ADC_PINS[i] ); // value between 0..4095
  }
  for ( int i=0; i < ADC_CHANNELS; i++ ) {
     sprintf( sbuf, "A%d=[%04d]", i, values[i]  );
     Serial.print( sbuf );
     if ( i == (ADC_CHANNELS-1) ) { 
        Serial.println(""); 
     } else {
        Serial.print(","); 
     }
  } 
  for ( int i=0; i < ADC_CHANNELS; i++ ) {
     volt = 3.3*values[i]/4095;
     sprintf( sbuf, "A%d=%d.%03dV", i, int(volt), int(volt*1000)%1000 );
     Serial.print( sbuf );
     if ( i == (ADC_CHANNELS-1) ) { 
        Serial.println("\n"); 
     } else {
        Serial.print(","); 
     }
  } 
  Serial.flush(); 
  delay( DELAY_MS );
}
////////////////////////////////////////////////////////////////////////////


