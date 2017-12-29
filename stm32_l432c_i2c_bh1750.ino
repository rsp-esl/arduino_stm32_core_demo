////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - BH1750 Light Sensor Interfacing Using I2C
//  - Tested with Nucleo L432KC Board
// Author: Rawat S.
// Date: 2017-12-29
////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
// see: https://github.com/stm32duino/Arduino_Core_STM32/tree/master/libraries/Wire

#define SCL_PIN          PB6   // PB_6 or D5 pin
#define SDA_PIN          PB7   // PB_7 or D4 pin

#define BH1750_I2CADDR             0x23
#define BH1750_CONT_HIGH_RES_MODE  0x10

TwoWire i2c( SDA_PIN, SCL_PIN );  
char sbuf[64];
 
bool bh1750_init() {
   i2c.beginTransmission( BH1750_I2CADDR );
   i2c.write((uint8_t) BH1750_CONT_HIGH_RES_MODE );
   uint8_t error = i2c.endTransmission();
   delay(10);
   if ( error != 0 ) {
      Serial.println( "No ACK from sensor !!!" );
      return false;
   }
   return true;
}

uint16_t bh1750_read() {
   uint16_t level;
   // Start transmission to sensor
   i2c.beginTransmission( BH1750_I2CADDR );
   // Read two bytes from sensor
   i2c.requestFrom( BH1750_I2CADDR, 2 );
   // Read two bytes, which are low and high parts of sensor value
   level = i2c.read();
   level <<= 8;
   level |= i2c.read();
   i2c.endTransmission();
   uint32_t lux = (10*(uint32_t)level)/12; // Convert raw value to lux
   return (uint16_t)lux;
}

void setup() {
   Serial.begin( 115200 );
   i2c.begin(); 
   i2c.setClock( 400000 );
   delay(10);
   while( !bh1750_init() ) {
     delay(1000);
   }
}

void loop() {
   uint16_t lux = bh1750_read();
   sprintf( sbuf, "Light: %5d Lux", lux );
   Serial.println( sbuf );
   delay(500); 
}
////////////////////////////////////////////////////////////////////////////

