// --------------------------------------
// Habilitar la EEPROM
//

#include <Wire.h>

#define GPIO 0x20

#define ENABLER 0x2D

#define PASS1 0x43
#define PASS2 0x4D
#define PASS3 0x53

#define VALUE 0x02

void setup()
{
  Wire.begin();
  
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nActivando la EEPROM");
  
  Serial.println("Escribiendo...");
  Wire.beginTransmission(GPIO);
  Wire.write((byte)ENABLER);
  Wire.write((byte)PASS1);
  Wire.write((byte)PASS2);
  Wire.write((byte)PASS3);
  Wire.write((byte)VALUE);
  int error = Wire.endTransmission();
  
  
  Serial.print("Acabado con error: ");Serial.println(error);
  
}


void loop()
{
  byte rdata = 0xF2;
  
  Serial.println("Checksum...");
  Wire.beginTransmission(GPIO);
  Wire.write(ENABLER);  
  
  int error = Wire.endTransmission();
  Serial.print("Acabado con error: ");Serial.println(error);
  
   Wire.requestFrom(GPIO,1);
    if (Wire.available()){
      rdata = Wire.read();
    }
  
  Serial.print("STATUS RECIBIDO: 0x");Serial.println(rdata,HEX);
  
  delay(20000);
}
