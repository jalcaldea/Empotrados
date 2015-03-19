// --------------------------------------
// Habilitar la EEPROM
//

#include <Wire.h>

#define GPIO 0x20
#define MEM 0x50

#define CONFIG 0x30
#define ENABLER 0x2D

#define PASS1 0x43
#define PASS2 0x4D
#define PASS3 0x53

#define VALUE 0x02
#define RESET_CMD 0x02


void turnUpEEPROM() {
  //Serial.print("\nActivando la EEPROM...");

  Wire.beginTransmission(GPIO);
  Wire.write((byte)ENABLER);
  Wire.write((byte)PASS1);
  Wire.write((byte)PASS2);
  Wire.write((byte)PASS3);
  Wire.write((byte)VALUE);
  int error = Wire.endTransmission();

  /*if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }*/

}

void reset() {
  //Serial.print("\nReseteando...");

  Wire.beginTransmission(GPIO);
  Wire.write((byte)CONFIG);
  Wire.write((byte)RESET_CMD);
  int error = Wire.endTransmission();
  /*if(error==0){
    Serial.println(" OK");
  }else{
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }*/
}

int save(unsigned int dir, byte data) {
  //Serial.print("\nGuardando en la EEPROM...");


  byte high = dir / 256;
  byte low = dir % 256;

  /*Serial.print(" -> Escribiendo en la direccion: ");
  Serial.print("0x");
  Serial.print(high,HEX);
  Serial.print(" 0x");
  Serial.print(low,HEX);
  Serial.print(" ...");*/

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.write(data);
  int error = Wire.endTransmission();


  return error;

}
  

int save(unsigned int dir, char* data) {
  //Serial.print("\nGuardando en la EEPROM...");


  byte high = dir / 256;
  byte low = dir % 256;

  /*Serial.print("Escribiendo en la direccion: ");
  Serial.print("0x");
  Serial.print(high,HEX);
  Serial.print(" 0x");
  Serial.println(low,HEX);*/

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.write(data);
  int error = Wire.endTransmission();

  return error;

}


byte read(unsigned int dir) {
  byte rdata = 242;

  byte high = dir / 256;
  byte low = dir % 256;

  /*Serial.print("Leyendo en la direccion: ");
  Serial.print("0x");
  Serial.print(high,HEX);
  Serial.print(" 0x");
  Serial.println(low,HEX);

  Serial.print("\Leyendo de la EEPROM...");*/

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  int error = Wire.endTransmission();

  Wire.requestFrom(MEM, 1);
  if (Wire.available()) {
    rdata = Wire.read();
  }

  /*if(error==0){
    Serial.println(" OK");
  }else{
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }*/

  return rdata;

}

void read2(unsigned int dir,byte* rdata, int len) {
  
  byte high = dir / 256;
  byte low = dir % 256;

  /*Serial.print("Leyendo en la direccion: ");
  Serial.print("0x");
  Serial.print(high,HEX);
  Serial.print(" 0x");
  Serial.println(low,HEX);

  Serial.print("\Leyendo de la EEPROM...");*/

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

  /*if(error==0){
    Serial.println(" OK");
  }else{
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }*/

}


void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);

}


void loop()
{

  Serial.println("INICIO\n\n");

  unsigned int i = 0;


  for(i=0; i< 32768;i++){

    if( (i%16)==0 ){
      Serial.print("\n0x");
      if(i<16){
        Serial.print("0");
      }
      if(i<256){
        Serial.print("0");
      }
      if(i<4096){
        Serial.print("0");
      }
      Serial.print(i,HEX);
      Serial.print(" - ");
    }

    byte hola = read(i);

     if(hola<16){
       Serial.print("0");
     }

     //int hola = save(i,(byte)48);
     Serial.print(hola,HEX);
     Serial.print(" ");
  }

  
  
 

  /*int prueba = 0;
  unsigned int i=11560;
  while(prueba==0){

    if( (i%16)==0 ){
      Serial.print("\n0x");
      if(i<16){
        Serial.print("0");
      }
      if(i<256){
        Serial.print("0");
      }
      if(i<4096){
        Serial.print("0");
      }
      Serial.print(i,HEX);
      Serial.print(" - ");
    }


    prueba = save(i,(byte)48);
    Serial.print(prueba);
    Serial.print(" ");
    i++;
  }*/


  Serial.println("\n======================= HEMOS ACABADO ==================================");
  /* for(byte i=1; i<24; i++){
     jeje = read(0,i);
     delay(2000);
     Serial.println(jeje);
   }*/

  delay(200000);
}
