////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - Analog Reading (Input Voltage between 0V to 3.3V)
//  - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-28
////////////////////////////////////////////////////////////////////////////
#define AIN_PIN       A0  // PA_0 or A0 pin (input voltage: 0V .. 3.3V only)
#define DELAY_MS      500

char sbuf[64];

void setup() {
  Serial.begin( 115200 );
  analogReadResolution(12); // use 12-bit ADC resolution (instead of 10bit)
}

void loop() {
  int value = analogRead( AIN_PIN ); // value between 0..4095
  float volt = 3.3*value/4095;
  sprintf( sbuf, "Reading A%d: %4d, %d.%03d V",
           (AIN_PIN-A0), value, int(volt), int(volt*1000)%1000 );
  Serial.println( sbuf );
  delay( DELAY_MS );
}
////////////////////////////////////////////////////////////////////////////


