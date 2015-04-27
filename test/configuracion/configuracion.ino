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

   Serial.print("Iniciando EEPROM...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)ENABLER);
  Wire.write((byte)PASS1);
  Wire.write((byte)PASS2);
  Wire.write((byte)PASS3);
  Wire.write((byte)VALUE);
  int error = Wire.endTransmission();

  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
  Serial.print("Configurando GPORT0...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)0);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT0);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
 
 
   Serial.print("Configurando GPORT1...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)1);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
    Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT1);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
 
 
 Serial.print("Configurando GPORT3...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)3);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT3);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
  
    Serial.print("Configurando GPORT2...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)2);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)1);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
    Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)1);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT2);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)3);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
    Serial.print("Configurando GPORT7...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)7);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  
    Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT7);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
    Serial.print("Configurando GPORT5...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)5);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT5);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
    Serial.print("Configurando GPORT6...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)6);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
      Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT6);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1E);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
   Serial.print("Configurando GPORT4...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)SELECT);
  Wire.write((byte)4);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }

  Wire.beginTransmission(GPIO);
  Wire.write((byte)DIRECTION);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
      Wire.beginTransmission(GPIO);
  Wire.write((byte)INTERRUPT);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)W_GPORT4);
  Wire.write((byte)0);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  Wire.beginTransmission(GPIO);
  Wire.write((byte)0x1D);
  Wire.write((byte)0XFF);
  error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.println(error);
  }
  
  
  Serial.print("GUARDANDO CONFIGURACION...");
   
  Wire.beginTransmission(GPIO);
  Wire.write((byte)COMMAND);
  Wire.write((byte)STORE);
  error = Wire.endTransmission();

  if (error == 0) {
    Serial.print(" OK");
  } else {
    Serial.print("COD ERROR: ");
    Serial.print(error);
  }
  
  
  
}


void loop(){
  
}
