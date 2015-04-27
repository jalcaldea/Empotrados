#include "IA.h"

#include "Arduino.h"
#include "Board.h"

	/*AUN SOLO BUSCA CON PROFUNDIDAD 1!!!!*/
	void IA::movimiento (Board t, byte jugador,byte (&pos)[2]){
		
		byte casillas[3] = {};
		t.getPosition(jugador,casillas);
		
		int beneficio1 = 0;
		//pos1 tiene la posicion de la ficha antes de ser movida y pos2 después
		byte pos1 = NIL;
		byte pos2 = NIL;
		//Por cada ficha..
		for (byte i=0; i<3; i++){
			//Por cada movimiento
			if(casillas[i]!= NIL){
				for (byte j=0; j<4; j++){
					if (posibleMov(t,casillas[i],j,jugador)){
						Serial.println("OK");
						int beneficio2 = beneficio(t, casillas[i], j, jugador,beneficio1 ,jugador,1);
						if (beneficio1<=beneficio2 || pos1 == NIL ){
							beneficio1 = beneficio2;
							pos1 = casillas[i];
							pos2 = t.newPosition(casillas[i],j,jugador);
						}
					}
				}
			}
		}
		pos[0] = pos1;
		pos[1] = pos2;
	}
	
	int IA::movimientoajeno (Board t, byte jugador, int& nuestro, byte siguiente,byte prof){
		
		byte casillas[3] = {};
		t.getPosition(siguiente,casillas);
		
		byte movs[] = {0,1,2,3};

		for (byte a=0; a<4; a++)
		{
		 int r = random(a,3); // dont remember syntax just now, random from a to 8 included.
		 byte temp = movs[a];
		 movs[a] = movs[r];
		 movs[r] = temp;
		}
		
		int beneficio1 = 0;
		//pos1 tiene la posicion de la ficha antes de ser movida y pos2 después
		byte pos1 = NIL;
		byte pos2 = NIL;
		//Por cada ficha..
		for (byte i=0; i<3; i++){
			//Por cada movimiento
			if(casillas[i]!= NIL){
				for (byte j=0; j<4; j++){
					if (posibleMov(t,casillas[i],j,siguiente)){
						Serial.println("OK");
						int beneficio2 = beneficio(t, casillas[i],j, jugador,nuestro, siguiente,prof);
						if (beneficio1<=beneficio2 || pos1 == NIL ){
							beneficio1 = beneficio2;
							pos1 = casillas[i];
							pos2 = t.newPosition(casillas[i],j,siguiente);
						}
					}
				}
			}
		}
	}
	
	
	//Devuelve true si es posible hacer un movimiento y false en caso contrario
	bool IA::posibleMov (Board t, byte pos, byte mov,byte jug){
	
		Serial.print("Probando de : ");
		Serial.print(pos);
		Serial.print(" ");
		Serial.println(mov);
		
		return (t.newPosition(pos,mov,jug)!=NIL);
	}
	
	//Devuelve el tablero resultante tras efectuar un movimiento
	Board IA::nuevoBoard (Board t, byte pos, byte mov,byte jugador){
		if(posibleMov(t, pos, mov,jugador)){
			byte nuevapos = t.move(pos, mov,jugador);
			t.remove(pos);
			t.set(pos,jugador);
		}else{
			return t;
		}
	}
	
	//Devuelve el beneficio de un movimiento.
	//Si en ese movimiento se pierde, el beneficio es -30
	int IA::beneficio (Board t, byte pos, byte mov, byte jugador, int& nuestro, byte siguiente,byte prof){
		int toReturn = 0;

			Board aux = Board();
			
			for(byte i=0;i<25;i++){
				aux.set(i,t.getPlayer(i));
			}
			
			aux.move(pos, mov,siguiente);
			aux.checkLimits();
			for(byte i=0; i<25; i++){
				if( aux.getPlayer(i)==siguiente && aux.blocked(i)){
					toReturn-=1;
				}else if(aux.getPlayer(i)!=siguiente && aux.getPlayer(i)!=0 && aux.blocked(i)){
					toReturn+=1;
				}
				/*if( aux.getPlayer(i)==jugador && aux.blocked(i)){
					nuestro-=1;
				}else if(  aux.getPlayer(i)!=jugador && aux.getPlayer(i)!=0 && aux.blocked(i)){
					nuestro+=1;
				}*/
			}
			if( t.getPositions(siguiente)==0){
				toReturn -= 30;
			}
			/*if(  t.getPositions(jugador)==0){
				nuestro += 30;
			}
			
			
			byte next = (jugador % 3) +1;
			
			if(prof>1){
				movimientoajeno(aux,jugador,nuestro, next,prof--);
			}
			
			Serial.println(nuestro);*/
			
		return toReturn;
		
	
}
