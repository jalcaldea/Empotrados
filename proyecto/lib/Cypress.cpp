#include "Cypress.h"

#define GPIO 0x20

int Cypress::turnUpEEPROM() {

  Wire.beginTransmission(GPIO);
  Wire.write((byte)ENABLER);
  Wire.write((byte)PASS1);
  Wire.write((byte)PASS2);
  Wire.write((byte)PASS3);
  Wire.write((byte)VALUE);
  return Wire.endTransmission();

}

int Cypress::save(unsigned int dir, byte data) {

  byte high = dir / 256;
  byte low = dir % 256;

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.write(data);
  int error = Wire.endTransmission();

  return error;

}


int Cypress::saveData(unsigned int dir, byte* data) {

  byte high = dir / 256;
  byte low = dir % 256;

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  Wire.write((char*)data);
  int error = Wire.endTransmission();

  return error;

}

byte Cypress::read(unsigned int dir) {
  
  byte high = dir / 256;
  byte low = dir % 256;

  byte rdata = NULL;

  Wire.beginTransmission(MEM);
  Wire.write((byte)high);
  Wire.write((byte)low);
  int error = Wire.endTransmission();

  Wire.requestFrom(MEM, 1);
  if (Wire.available()) {
      rdata = Wire.read();
  }
  
  return rdata;

}

void Cypress::readData(unsigned int dir,byte* rdata, int len) {
  
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

byte Cypress::readReg(byte reg){
  Wire.beginTransmission(GPIO);
  Wire.write((byte)reg);
  Wire.endTransmission(false);
  byte rdata = 0;
  
   Wire.requestFrom(GPIO,1);
    if (Wire.available()){
      rdata = Wire.read();
    }
   Wire.endTransmission();
    
    return rdata;
}

void Cypress::readRegData(byte reg,byte* rdata, int len){

  Wire.beginTransmission(GPIO);
  Wire.write(reg);
  Wire.endTransmission(false);
  
  
  Wire.requestFrom(GPIO, len);
  int c = 0;
  for ( c = 0; c < len; c++ ) {
    if (Wire.available()) {
      rdata[c] = Wire.read();
    }
  }
   Wire.endTransmission();
}


int Cypress::writeReg(byte reg, byte val){
  Wire.beginTransmission(GPIO);
  Wire.write(reg);
  Wire.write(val);
  return Wire.endTransmission();
  
}
