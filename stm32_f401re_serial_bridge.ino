////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - Hardware Serial Bridge (Serial <--> Serial1)
//  - Tested with Nucleo F401RE Board
// Author: Rawat S.
// Date: 2017-12-29
////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin( 115200 );   // Serial = Serial2 for Nucleo F401RE Board
  Serial1.begin( 115200 );  // PA_9/D8=TX, PA_10/D2=RX (UART1)
}

void loop() {
  while ( Serial.available() > 0 ) {
     // read one char from Serial Rx and write it to Serial1 Tx
     char ch = Serial.read(); 
     Serial1.write( ch );
  }
  while ( Serial1.available() > 0 ) {
     // read one char from Serial1 Rx and write it to Serial Tx
     char ch = Serial1.read();
     Serial.write( ch );
  }
}
///////////////////////////////////////////////////////////////////////////

