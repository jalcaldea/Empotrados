// --------------------------------------
// Habilitar la EEPROM
//

#include <Wire.h>

#define GPIO 0x20
#define MEM 0x50

#define ENABLER 0x2D
#define DIRECTION 0x1C

#define R_GPORT0 0x00
#define W_GPORT0 0x08

#define R_GPORT1 0x01
#define W_GPORT1 0x09

#define PWM_SEL 0x1A

#define PASS1 0x43
#define PASS2 0x4D
#define PASS3 0x53

#define VALUE 0x02

#define LASTDIR 27647
#define NULL 0xF2

#define STATUS 0x2E

int turnUpEEPROM() {

  Wire.beginTransmission(GPIO);
  Wire.write((byte)ENABLER);
  Wire.write((byte)PASS1);
  Wire.write((byte)PASS2);
  Wire.write((byte)PASS3);
  Wire.write((byte)VALUE);
  Wire.endTransmission();

  return save(LASTDIR, NULL);

}


int save(unsigned int dir, byte data) {

  byte high = dir / 256;
  byte low = dir % 256;

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.write(data);
  int error = Wire.endTransmission();

  return error;

}
  

int saveData(unsigned int dir, char* data) {


  byte high = dir / 256;
  byte low = dir % 256;

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.write(data);
  int error = Wire.endTransmission();

  return error;

}


byte read(unsigned int dir) {
  byte rdata = NULL;

  byte high = dir / 256;
  byte low = dir % 256;


  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.endTransmission();

  Wire.requestFrom(MEM, 1);
  if (Wire.available()) {
    rdata = Wire.read();
  }

  return rdata;

}

void readData(unsigned int dir,byte* rdata, int len) {
  
  byte high = dir / 256;
  byte low = dir % 256;


  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  int error = Wire.endTransmission();

  Wire.requestFrom(MEM, len);
  int c = 0;
  for ( c = 0; c < len; c++ ) {
    if (Wire.available()) {
      rdata[c] = Wire.read();
    }
  }

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
void setup(){
  
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);

   Serial.print("Iniciando...");
  /*int error = turnUpEEPROM();

  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }*/
  
}


void loop()
{

  Serial.println("INICIO\n\n");

  /*Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT1);
  Wire.write((byte)10);
  Wire.endTransmission();*/
  
  /* Wire.beginTransmission(GPIO);
  Wire.write(W_GPORT0);
  Wire.write((byte)255);
  int error = Wire.endTransmission();*/
  
  Serial.println("Estos son los valores de GPORT0...");
  
  byte rdata = 0;
  
  byte dir = 0;
  for(dir=0;dir<49;dir++){ //antes el 8 era un 49
    
    Serial.print("0x");
    if(dir<16){
      Serial.print("0");
    }
    
    Serial.print(dir,HEX);
    
    Serial.print(" - ");
    
    
    rdata = readReg(dir);
  

    if((dir<24)||(dir>24 && dir <30)){
      
          if(rdata<2){
            Serial.print("0");
          }
          if(rdata<4){
            Serial.print("0");
          }
          if(rdata<8){
            Serial.print("0");
          }
          if(rdata<16){
            Serial.print("0");
          }
          if(rdata<32){
            Serial.print("0");
          }
          if(rdata<64){
            Serial.print("0");
          }
          if(rdata<128){
            Serial.print("0");
          }
      
          Serial.print(rdata,BIN);
      
    }else{
           Serial.print("   --   ");
      
    }
           Serial.print("   ");
            if(rdata<16){
             Serial.print("0");
           }
          Serial.println(rdata,HEX);

  }
 
  /*Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT0);
  Wire.write((byte)0);
  Wire.endTransmission();*/
 
  /*Wire.beginTransmission(GPIO);
  Wire.write((byte)0x30);
  Wire.write((byte)0x01);
  Wire.endTransmission();*/
 
  Serial.println("\n======================= HEMOS PUTO ACABADO ==================================");

  delay(2000);
}
