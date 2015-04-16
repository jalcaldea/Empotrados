// --------------------------------------
// Habilitar la EEPROM
//

#include <Wire.h>

#define GPIO 0x20
#define MEM 0x50

#define SELECT 0x18
#define INTERRUPT 0x19
#define ENABLER 0x2D
#define DIRECTION 0x1C
#define COMMAND 0x30

#define W_GPORT0 0x08
#define W_GPORT1 0x09
#define W_GPORT2 0x0A
#define W_GPORT3 0x0B
#define W_GPORT4 0x0C
#define W_GPORT5 0x0D
#define W_GPORT6 0x0E
#define W_GPORT7 0x0F

#define PASS1 0x43
#define PASS2 0x4D
#define PASS3 0x53

#define VALUE 0x02

#define STORE 0x01

void setup(){
  
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);
  
  
}

  byte readReg(byte reg){
  Wire.beginTransmission(GPIO);
  Wire.write(reg);
  Wire.endTransmission(false);
  
  byte rdata = NULL;
  
   Wire.requestFrom(GPIO,1);
    if (Wire.available()){
      rdata = Wire.read();
    }
   Wire.endTransmission();
    
    return rdata;
  }


void loop(){
  
  
  Serial.print("Configurando GPORT0...");
  /*int led=1;
  
  byte i=13;
  
  for(i=13;i<16;i++){
    
    int j = 1;
    //for(j=1;j<129;j*=2){
      
        Serial.print("Encendiendo led ");
        Serial.print(led++);
        Serial.print(" ...");
        Wire.beginTransmission(GPIO);
        Wire.write((byte)i);
        Wire.write((byte)0xFF);
        int error = Wire.endTransmission();
      
        if (error == 0) {
          Serial.println(" OK");
        } else {
          Serial.println("COD ERROR: ");
          Serial.print(error);
        }
      
        //delay(1000);
      
    //}
    
  }
  
        Serial.print("Encendiendo led ");
        Serial.print(led++);
        Serial.print(" ...");
        Wire.beginTransmission(GPIO);
        Wire.write((byte)0x0A);
        Wire.write((byte)2);
        int error = Wire.endTransmission();
      
        if (error == 0) {
          Serial.println(" OK");
        } else {
          Serial.println("COD ERROR: ");
          Serial.print(error);
        }
  
   delay(1000);*/
   
   
   
  byte rdata = 0;
  
  byte dir = 0;
  
  rdata = readReg(dir);

  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x0D);
  Wire.write((byte)rdata);
  Wire.endTransmission();
  
  rdata = 0;
  
  dir = 1;
  
  rdata = readReg(dir);

  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x0E);
  Wire.write((byte)rdata);
  Wire.endTransmission();
  
  rdata = 0;
  
  dir = 3;
  
  rdata = readReg(dir);

  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x0F);
  Wire.write((byte)rdata);
  Wire.endTransmission();
  
  rdata = 0;
  
  dir = 2;
  
  rdata = readReg(dir);

  rdata = rdata / 2;
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x0A);
  Wire.write((byte)rdata);
  Wire.endTransmission();
  
   
}
