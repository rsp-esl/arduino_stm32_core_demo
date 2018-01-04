
#define DAC_PIN   A2 // for DAC1/1 on Nucleo L053R8
// see: https://os.mbed.com/platforms/ST-Nucleo-L053R8/

int value = 0;
char sbuf[64];
int pm = 1;

void setup() {
  Serial.begin( 115200 );
  Serial.print( F("\n\n\n") );
  sprintf( sbuf, "System clock frequency %d MHz\n", SystemCoreClock/1000000 );
  Serial.print( sbuf );
  Serial.flush();
  
  pinMode( DAC_PIN, OUTPUT );
  
#ifndef HAL_DAC_MODULE_ENABLED
  Serial.println( "DAC is not supported !!!" );
#endif

  analogWriteResolution( 12 );
  analogWrite( DAC_PIN, value );
  
}

#define VALUE_MAX  4095
#define VALUE_MIN  0

void loop() {
  value += pm*10;
  if ( value > VALUE_MAX ) {
    value = VALUE_MAX; 
  } else if ( value < VALUE_MIN ) { 
    value = VALUE_MIN; 
  }
  analogWrite( DAC_PIN, value );
  if ( value >= VALUE_MAX && pm == 1 ){
     pm = -1;
  }  else if ( value <= VALUE_MIN && pm == -1 ){
     pm = 1;
  }
  delay(5);
}
