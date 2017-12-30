////////////////////////////////////////////////////////////////////////////
// Demo STM32 Core Support for Arduino:
//  - SHT3x-DIS (I2C) Light Sensor Interfacing Using I2C
//  - Tested with Nucleo L432KC Board
// Author: Rawat S.
// Date: 2017-12-29
////////////////////////////////////////////////////////////////////////////
// Sensirion SHT30-DIS Sensor Modules (SHT30 / SHT31 / SHT35)
//  - I2C, 16 bit data, VCC 2.4V to 5.5V, -40 to 125 °C, 0..100% RH
//  - SHT30-DIS-B +/-0.3 deg.C, +/-3.0 %RH 
//  - SHT31-DIS-B +/-0.3 deg.C, +/-2.0 %RH 
//  - SHT35-DIS-B +/-0.2 deg.C, +/-1.5 %RH
////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
// see: https://github.com/stm32duino/Arduino_Core_STM32/tree/master/libraries/Wire

#define SHT3x_I2C_ADDR         0x44  // SHT3x-DIS (I2C)
#define SHT3x_SOFT_RESET       0x30A2
// single shot mode, no clock stretching
#define SHT3x_ACCURACY_HIGH    0x2C06
#define SHT3x_ACCURACY_MEDIUM  0x2C0D
#define SHT3x_ACCURACY_LOW     0x2C10
    
#define SCL_PIN      PB6   // PB_6 or D5 pin
#define SDA_PIN      PB7   // PB_7 or D4 pin

TwoWire i2c( SDA_PIN, SCL_PIN );

char sbuf[64];
uint32_t ts;
float temp, humid;
uint8_t data[6]; 

// CRC-8, Polynomial: 0x31  x^8 + x^5 + x^4 + 1, Initial value = 0xff
uint8_t CRC8( uint8_t data[], uint8_t len ) {
  uint8_t crc = 0xFF;
  for ( uint8_t i=0; i < len; i++ ) {
    crc ^= data[i];
    for ( uint8_t j=0; j < 8; j++ ) {
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }
  }
  return crc;
}

void sht3x_init() {
  // Start I2C Transmission
  i2c.beginTransmission( SHT3x_I2C_ADDR );
  // Send soft reset command
  i2c.write( (SHT3x_SOFT_RESET >> 8) & 0xff );
  i2c.write( SHT3x_SOFT_RESET & 0xff ); 
  i2c.endTransmission();  // Stop I2C transmission
  delay(10);
  i2c.beginTransmission( SHT3x_I2C_ADDR );
  // Send soft reset command
  i2c.write( (SHT3x_ACCURACY_HIGH >> 8) & 0xff );
  i2c.write( SHT3x_ACCURACY_HIGH & 0xff ); 
  i2c.endTransmission();  // Stop I2C transmission
}

bool sht3x_read_sensor() {
  // Start I2C Transmission
  i2c.beginTransmission( SHT3x_I2C_ADDR );
  // Send measurement command
  i2c.write( (SHT3x_ACCURACY_HIGH >> 8) & 0xff );
  i2c.write( SHT3x_ACCURACY_HIGH & 0xff ); 
  i2c.endTransmission();  // Stop I2C transmission
  delay(50); // note: measurement time is about 15 msec
  // Request 6 bytes of data
  i2c.requestFrom( SHT3x_I2C_ADDR, 6 ); // request 6 bytes
  if ( i2c.available() == 6 ) {
    data[0] = i2c.read(); // temperature Celsius (MSB: high byte)
    data[1] = i2c.read(); // temperature Celsius (LSB: low byte)
    data[2] = i2c.read(); // temperature Celsius CRC
    data[3] = i2c.read(); // relative humidty (%RH) (MSB: high byte)
    data[4] = i2c.read(); // relative humidty (%RH) (LSB: low byte)
    data[5] = i2c.read(); // relative humidty CRC
  } else {
    return false;
  }
  // check CRC for both values
  if ( CRC8(data,2)==data[2] && CRC8(data+3,2)==data[5] ) {
    uint16_t value;
    value = (data[0] << 8) + data[1];
    temp  = ((value * 175.0) / 65535) - 45; // temperature in Celsius.
    value = (data[3] << 8) + data[4];
    humid = ((value * 100.0) / 65535); // relative humidity
    return true;
  } 
  return false;  
}

void setup() {
  Serial.begin( 115200 );  // set serial baudrate to 115200
  i2c.begin( );            // start the I2C bus
  i2c.setClock( 400000 );  // set I2C clock frequency to 400kHz
  sht3x_init();            // initalize the SHT3x-DIS
  ts = millis();
}

void loop() {
  if ( millis() - ts >= 1000 ) { // read sensor every 1000 msec
    String str;
    ts += 1000;
    if ( sht3x_read_sensor() ) {
      str = "";
      dtostrf( humid, 3, 1, sbuf );
      str += "Humidity: ";
      str += sbuf;
      str += " %RH, ";
      dtostrf( temp, 3, 1, sbuf );
      str += "Temperature: ";
      str += sbuf;
      str += " deg.C";
      Serial.println( str.c_str() );
    } 
    else {
      Serial.println( "Sensor reading  failed..." );
    }
  }
}
///////////////////////////////////////////////////////////////////////////


