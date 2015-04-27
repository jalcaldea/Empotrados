


/*
  Empotrados
  Prctica de empotrados
  
  Modulo principal de la aplicacion
  del juego de mesa con Arduino

  by:
  - Jesus Alcalde
  - Adrian Gutierrez
  - Javier Jimenez
 */
 
#include <Wire.h>
#include <Cypress.h>
#include <Board.h>
#include <IA.h>

byte player = 2;

byte mask_int[4] = {0,0,0,0};
bool mask[25] = {};
bool mask_temp[25] = {};
bool inicial = true;
Board board = Board();
byte turno = 1;

byte jugador = 0;

void leerTablero(byte jug){
  
  mask_int[0] = 0;
  mask_int[1] = 0;
  mask_int[2] = 0;
  mask_int[3] = 0;
  byte pos = NIL;
  
  do{
    
  bool verificado = false;
  
  while(!verificado){
    
    byte aux[4] = {};
    
  while(aux[0]==0 && aux[1]==0 && aux[3]==0 && aux[2]==0){
        Cypress::readRegData(INT_0,aux,(byte)4);
  }
  
        mask_int[0] = aux[0];
        mask_int[1] = aux[1];
        mask_int[2] = aux[3];
        mask_int[3] = aux[2];
    
        pos = getMaskTemp();
        if(jugador==jug && (cambiosTemp()==1 && (board.getPlayer(pos)==jug || inicial))){
          verificado = true;
          if(!inicial){
            if(pos>4 && board.getPlayer(pos-5)==0){
              turnOn(pos-5);
            }
            if(((pos % 5) != 4) && board.getPlayer(pos+1)==0){
              turnOn(pos+1);
            }
            
            if(pos<20 && board.getPlayer(pos+5)==0){
              turnOn(pos+5);
            }
            if(((pos % 5) != 0)&& board.getPlayer(pos-1)==0){
              turnOn(pos-1);
            }
          }else{
            
           for(byte k=0;k<10;k++){
             toggle(pos);
             delay(100);
           }
          }
          
        }else{
          
            /*mask_int[0] =0;
            mask_int[1] = 0;
            mask_int[2] = 0;
            mask_int[3] = 0;*/
          
          //ERROR
        }
        
        
        
}
        mask_int[0] = 0;
        mask_int[1] = 0;
        mask_int[2] = 0;
        mask_int[3] = 0;
        
        getMask();

   verificado = false;
   
  while(!verificado && !inicial){
    
    byte aux[4] = {};
    
  while(aux[0]==0 && aux[1]==0 && aux[3]==0 && aux[2]==0){
        Cypress::readRegData(INT_0,aux,(byte)4);
        
        if(pos>4 && board.getPlayer(pos-5)==0){
              toggle(pos-5);
            }
            if(((pos % 5) != 4) && board.getPlayer(pos+1)==0){
              toggle(pos+1);
            }
            
            if(pos<20 && board.getPlayer(pos+5)==0){
              toggle(pos+5);
            }
            if(((pos % 5) != 0)&& board.getPlayer(pos-1)==0){
              toggle(pos-1);
            }
            
         delay(200);
        
  }
    
        
    
        mask_int[0] = aux[0];
        mask_int[1] = aux[1];
        mask_int[2] = aux[3];
        mask_int[3] = aux[2];
    
        byte pos2 = getMask();
        if((cambios()==1) && board.getPlayer(pos2)==0 && (((pos2 == pos-5) && (pos2 > 0)) || ((pos2 == pos+5) && (pos2<25)) || ((pos2 == pos-1) && ((pos % 5) != 0)) || ((pos2 == pos+1) && ((pos % 5) != 4) ))){
            verificado = true;
          
            if(pos>4){
              turnOff(pos-5);
            }
            if((pos % 5) != 4){
              turnOff(pos+1);
            }
            
            if(pos<20){
              turnOff(pos+5);
            }
            if((pos % 5) != 0){
              turnOff(pos-1);
            }
        }else{
            mask_int[0] =0;
            mask_int[1] = 0;
            mask_int[2] = 0;
            mask_int[3] = 0;
          
          
          //ERROR
        }
}

  for(byte i = 0;i<25;i++){
      mask[i] = mask[i] || mask_temp[i];
      
      if(mask[i]){
        Serial.print("1 ");
      }else{
        Serial.print("0 ");
      }
      
  }
Serial.println();

  }while(!board.actualize(mask,jug,inicial));
          
}

byte cambiosTemp(){
   
  byte count=0;
  
  //Serial.println("Calculando mask TEMP");
  for(byte i=0;i<25;i++){
    if(mask_temp[i]){
      //Serial.print("1 ");
      count++;
    }else{
      //Serial.print("0 ");
    }    
  }
  
      //Serial.println();
  
  return count;
}

byte cambios(){
   
  byte count=0;
  
  Serial.println("Calculando mask");
  for(byte i=0;i<25;i++){
    if(mask[i]){
      Serial.print("1 ");
      count++;
    }else{
      Serial.print("0 ");
    }    
  }
  
      Serial.println();
  
  return count;
}

byte getMaskTemp(){
  
  byte aux  = 0;
  int pos = 0;
  for(byte i =0;i<3;i++){
    
    aux = mask_int[i];
    
    pos = 7*i + 7+i;
    
    mask_temp[pos--] = ((aux / 128)==1);   
    aux = aux % 128;
    
    mask_temp[pos--] = ((aux / 64)==1);
    aux = aux % 64;
     
    mask_temp[pos--] = ((aux / 32)==1);
    aux = aux % 32;
    
    mask_temp[pos--] = ((aux / 16)==1);
    aux = aux % 16;
    
    mask_temp[pos--] = ((aux / 8)==1);
    aux = aux % 8;
    
    mask_temp[pos--] = ((aux / 4)==1);
    aux = aux % 4;
    
    mask_temp[pos--] = ((aux / 2)==1);
    aux = aux % 2;
      
    mask_temp[pos] = (aux==1);

  }
  
    aux = mask_int[3];
    
    mask_temp[24] = ((aux %2 )== 1);
    
    
    byte i = 0;
    bool encontrado = false;
    byte toReturn = NIL;
    
    while(i<25 && !encontrado){
      
      if(mask_temp[i]){
        encontrado = true;
        toReturn = i;
      }
      i++;
    }
    
    return toReturn;
  
}


byte getMask(){
  
  byte aux  = 0;
  int pos = 0;
  for(byte i =0;i<3;i++){
    
    aux = mask_int[i];
    
    pos = 7*i + 7+i;
    
    mask[pos--] = ((aux / 128)==1);   
    aux = aux % 128;
    
    mask[pos--] = ((aux / 64)==1);
    aux = aux % 64;
     
    mask[pos--] = ((aux / 32)==1);
    aux = aux % 32;
    
    mask[pos--] = ((aux / 16)==1);
    aux = aux % 16;
    
    mask[pos--] = ((aux / 8)==1);
    aux = aux % 8;
    
    mask[pos--] = ((aux / 4)==1);
    aux = aux % 4;
    
    mask[pos--] = ((aux / 2)==1);
    aux = aux % 2;
      
    mask[pos] = (aux==1);

  }
  
    aux = mask_int[3];
    
    mask[24] = ((aux %2 )== 1);
    
    
    byte i = 0;
    bool encontrado = false;
    byte toReturn = NIL;
    
    while(i<25 && !encontrado){
      
      if(mask[i]){
        encontrado = true;
        toReturn = i;
      }
      i++;
    }
    
    return toReturn;
  
}


void actualizarTablero(){
  
        for(byte i =0;i<25;i++){
           if(board.getPlayer(i)==9){
              turnOn(i); 
           }else{
               turnOff(i);
           }
        }

        byte comidas[9] = {};
        byte aux[4] = {};
        board.getEliminated(comidas);
        
        byte i = 0;
        
        while(comidas[0]!=NIL){
         
              for(byte i=0;i<9;i++){
              Serial.print(comidas[i]);
              Serial.print(" ");
              }
                 Serial.print("\n");

                    
               aux[0] = 0;
               aux[1] = 0;
               aux[2] = 0;
               aux[3] = 0;
         
         while(aux[0]==0 && aux[1]==0 && aux[3]==0 && aux[2]==0){
            Cypress::readRegData(INT_0,aux,(byte)4);
            toggle(comidas[i]);
            delay(200);
         }
            
           mask_int[0] = aux[0];
            mask_int[1] = aux[1];
            mask_int[2] = aux[3];
            mask_int[3] = aux[2];
    
        byte pos = getMask();
            Serial.println(cambios());
            Serial.println(pos);
            Serial.println(comidas[0]);
            if(cambios()==1 && comidas[0]==pos){
                 board.comer(inicial);
                 turnOff(pos);
                 
                 board.getEliminated(comidas);
                   
                 
            }else{
              mask_int[0] = 0;
              mask_int[1] = 0;
              mask_int[2] = 0;
              mask_int[3] = 0;
            }
         
          
        }
  
}

void turnOn(byte pos){

  if(pos<8){
      byte aux = Cypress::readReg(W_GPORT5);
      
      byte tmp = 1;
      
      for(byte i=1;i<=pos;i++){
        tmp *= 2;
      }
      
      aux = aux | tmp;
      
      Cypress::writeReg(W_GPORT5,aux);
      
  }else if(pos<16){
    byte aux = Cypress::readReg(W_GPORT6);
    
       byte tmp = 1;
      
      for(byte i=1;i<=(pos-8);i++){
        tmp *= 2;
      }
      
      aux = aux | tmp;
      
      Cypress::writeReg(W_GPORT6,aux);
    
    
  }else if(pos<24){
    byte aux = Cypress::readReg(W_GPORT7);
    
    byte tmp = 1;
      
      for(byte i=1;i<=(pos-16);i++){
        tmp *= 2;
      }
      
      aux = aux | tmp;
      
      Cypress::writeReg(W_GPORT7,aux);
    
  }else if(pos==24){
    byte aux = Cypress::readReg(W_GPORT2);
    
    aux = aux | (byte)2;
      
    Cypress::writeReg(W_GPORT2,aux);
    
  }
  
}

void turnOff(byte pos){
 
    

  if(pos<8){
      byte aux = Cypress::readReg(W_GPORT5);
      
      byte tmp = 1;
      
      for(byte i=1;i<=pos;i++){
        tmp *= 2;
      }
      
      aux = aux & ~tmp;
      
      Cypress::writeReg(W_GPORT5,aux);
      
  }else if(pos<16){
    byte aux = Cypress::readReg(W_GPORT6);
    
       byte tmp = 1;
      
      for(byte i=1;i<=(pos-8);i++){
        tmp *= 2;
      }
      
      aux = aux & ~tmp;
      
      Cypress::writeReg(W_GPORT6,aux);
    
    
  }else if(pos<24){
    byte aux = Cypress::readReg(W_GPORT7);
    
    byte tmp = 1;
      
      for(byte i=1;i<=(pos-16);i++){
        tmp *= 2;
      }
      
      aux = aux & ~tmp;
      
      Cypress::writeReg(W_GPORT7,aux);
    
  }else if(pos==24){
    byte aux = Cypress::readReg(W_GPORT2);
    
    aux = aux & ~(byte)2;
      
    Cypress::writeReg(W_GPORT2,aux);
    
  }
  
}


void toggle(byte pos){
 
    

  if(pos<8){
      byte aux = Cypress::readReg(W_GPORT5);
      
      byte tmp = 1;
      
      for(byte i=1;i<=pos;i++){
        tmp *= 2;
      }
      
      aux = aux ^ tmp;
      
      Cypress::writeReg(W_GPORT5,aux);
      
  }else if(pos<16){
    byte aux = Cypress::readReg(W_GPORT6);
    
       byte tmp = 1;
      
      for(byte i=1;i<=(pos-8);i++){
        tmp *= 2;
      }
      
      aux = aux ^ tmp;
      
      Cypress::writeReg(W_GPORT6,aux);
    
    
  }else if(pos<24){
    byte aux = Cypress::readReg(W_GPORT7);
    
    byte tmp = 1;
      
      for(byte i=1;i<=(pos-16);i++){
        tmp *= 2;
      }
      
      aux = aux ^ tmp;
      
      Cypress::writeReg(W_GPORT7,aux);
    
  }else if(pos==24){
    byte aux = Cypress::readReg(W_GPORT2);
    
    aux = aux ^ (byte)2;
      
    Cypress::writeReg(W_GPORT2,aux);
    
  }
  
}


// the setup function runs once when you press reset or power the board
void setup() {
  
  Wire.begin();
  //Serial.begin(9600);
  //while(!Serial);
  
  for(int i=0;i<25;i++){
    mask[i] = false;
    mask_temp[i] = false;
  }
  actualizarTablero();
 /* inicial = false;
  
  board.set(5,3);
  board.set(7,1);
  board.set(9,3);
  board.set(11,2);
  board.set(14,2);
  board.set(15,3);
  board.set(17,1);
  board.set(19,1);
  board.set(20,1);
  board.set(21,2);*/

  for(byte i=0;i<25;i++){
    Serial.print(board.getPlayer(i));
    Serial.print(" ");
    if(i%5 == 4){
       Serial.print("\n");
    }
  }
  Serial.println("=== T =====");
  
  
}

void printMask(){
  Serial.print(mask_int[0],HEX);
  Serial.print(" ");
  Serial.print(mask_int[1],HEX);
  Serial.print(" ");
  Serial.print(mask_int[2],HEX);
  Serial.print(" ");
  Serial.print(mask_int[3],HEX);
  Serial.println();
}

// the loop function runs over and over again forever
void loop() {
  
  
   for(byte jug=1;jug<4;jug++){
    
     //player = jug;
     
     if((inicial || board.getPositions(jug)>0) && (jug!=player || inicial) ){
       
     jugador = jug;
       
     Serial.print("Turno del jugador: ");
     Serial.println(jug);
     
     
     leerTablero(jug);
     turno++;
     
     if(turno>9){
      board.checkLimits();
      inicial = false; 
     }
       
    
    for(byte i=0;i<25;i++){
    Serial.print(board.getPlayer(i));
    Serial.print(" ");
    if(i%5 == 4){
       Serial.print("\n");
    }
    
    actualizarTablero();
    
    
  }
  Serial.println("=== T =====");
     
     
     delay(100);
     
     }else if(jug==player && board.getPositions(jug)>0){
     
         Serial.println("ME TOCA!");
   
         byte mov[2] = {};
   
         IA::movimiento(board, jug,mov);      
      
         
         mask_int[0] = 0;
  mask_int[1] = 0;
  mask_int[2] = 0;
  mask_int[3] = 0;
  byte pos = NIL;
  
  do{
    
  bool verificado = false;
  
  while(!verificado){
    
    byte aux[4] = {};
    
  while(aux[0]==0 && aux[1]==0 && aux[3]==0 && aux[2]==0){
        Cypress::readRegData(INT_0,aux,(byte)4);
        
        toggle(mov[0]);
        toggle(mov[1]);
        delay(200);
  }
  
        mask_int[0] = aux[0];
        mask_int[1] = aux[1];
        mask_int[2] = aux[3];
        mask_int[3] = aux[2];
    
        pos = getMaskTemp();
        if(cambiosTemp()==1 && (pos==mov[0])){
          verificado = true;
          
           turnOff(pos);
          
          
        }else{
          
            /*mask_int[0] =0;
            mask_int[1] = 0;
            mask_int[2] = 0;
            mask_int[3] = 0;*/
          
          //ERROR
        }
        
        
        
}
        mask_int[0] = 0;
        mask_int[1] = 0;
        mask_int[2] = 0;
        mask_int[3] = 0;
        
        getMask();

   verificado = false;
   
  while(!verificado){
    
    byte aux[4] = {};
    
  while(aux[0]==0 && aux[1]==0 && aux[3]==0 && aux[2]==0){
        Cypress::readRegData(INT_0,aux,(byte)4);
         toggle(mov[1]);
         delay(200);    
  }
    
        
    
        mask_int[0] = aux[0];
        mask_int[1] = aux[1];
        mask_int[2] = aux[3];
        mask_int[3] = aux[2];
    
        byte pos2 = getMask();
        if(pos2==mov[1]){
            verificado = true;
            turnOff(pos2);
        }else{
            mask_int[0] = 0;
            mask_int[1] = 0;
            mask_int[2] = 0;
            mask_int[3] = 0;
          
          
          //ERROR
        }
}

  for(byte i = 0;i<25;i++){
      mask[i] = mask[i] || mask_temp[i];
      
      if(mask[i]){
        Serial.print("1 ");
      }else{
        Serial.print("0 ");
      }
      
  }
Serial.println();

  }while(!board.actualize(mask,player,inicial));
          
      for(byte i=0;i<25;i++){
    Serial.print(board.getPlayer(i));
    Serial.print(" ");
    if(i%5 == 4){
       Serial.print("\n");
    }
    
    actualizarTablero();
      
      }Serial.println();   
     
  }
   
   }
  
}
