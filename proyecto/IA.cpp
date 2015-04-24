#include Arduino.h
#include Board.h

class IA{
	public:
	
	/*
		los movimentos son:
		0- arriba
		1- derecha
		2- abajo
		3- izquierda
	*/
	
	/**
		Devuelve un array con 2 posiciones:
		1- Casilla que tiene la ficha a mover
		2- Casilla a la que mover la ficha
	*/
	/*AUN SOLO BUSCA CON PROFUNDIDAD 1!!!!*/
	byte[2] movimiento (Board t, byte jugador){
		
		byte casillas[] = t-> getPositions(jugador);
		
		byte beneficio = 0;
		//pos1 tiene la posicion de la ficha antes de ser movida y pos2 después
		byte pos1 = -1;
		byte pos2 = -1;
		//Por cada ficha..
		for (byte i=0; i<casillas.length; i++){
			//Por cada movimiento
			for (byte j=0; j<4; j++){
				if (posibleMov(t,i,j)){
					byte beneficio2 = this.beneficio(t, i, j, jugador);
					if (beneficio<beneficio2 || pos1 = -1){
						beneficio = beneficio2;
						pos1 = i;
						pos2 = t.newPosition(i,j);
					}
				}
			}
		}
		return {pos1, pos2};
	}
	
	private:
	
	//Devuelve true si es posible hacer un movimiento y false en caso contrario
	bool posibleMov (Board t, byte pos, byte mov){
		return !((pos<4 && mov==0) || (pos>20 && mov==2) ||
			(pos==24 && mov==1) || (pos==0 && mov==3) ||
			(t.getPlayer(pos)!=0));
	}
	
	//Devuelve el tablero resultante tras efectuar un movimiento
	Board nuevoBoard (Board t, byte pos, byte mov){
		if(posibleMov(pos, mov)){
			byte nuevapos = mueve(pos, mov);
			t.remove(pos);
			t.set(pos);
		}else{
			return t;
		}
	}
	
	//Devuelve el beneficio de un movimiento.
	//Si en ese movimiento se pierde, el beneficio es -30
	byte beneficio (Board t, byte pos, byte mov, byte jugador){
		byte toReturn = 0;
		byte newPos = t.newPosition(pos, mov);
		if(newPos == -1){
			return newPos;
		}else{
			Board aux = copyBoard(t);
			aux.move(pos, newPos);
			for(byte i=0; i<25; i++){
				if(aux.getPlayer(i)==jugador && aux.blocked(i)){
					toReturn-=1;
					t.remove(i);
				}else if(aux.getPlayer(i)!=1 && aux.getPlayer(i)!=0 && aux.blocked(i)){
					toReturn+=1;
					t.remove(i);
				}
			}
			if(t.getPositions(jugador).lenght==0){
				toReturn = -30;
			}
		}
		return toReturn;
		
	}
}