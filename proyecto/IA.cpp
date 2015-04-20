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
	int[2] movimiento (Board t, int jugador){
		
		int casillas[] = t-> getPositions(jugador);
		
		int beneficio = 0;
		//pos1 tiene la posicion de la ficha antes de ser movida y pos2 después
		int pos1 = -1;
		int pos2 = -1;
		//Por cada ficha..
		for (int i=0; i<casillas.length; i++){
			//Por cada movimiento
			for (int j=0; j<4; j++){
				if (posibleMov(t,i,j)){
					int beneficio2 = this.beneficio(t, i, j);
					if (beneficio<beneficio2 || pos1 = -1){
						beneficio = beneficio2;
						pos1 = i;
						pos2 = mueve(i,j);
					}
				}
			}
		}
	}
	
	private:
	
	//Devuelve la nueva posición de una ficha tras ser movida
	int mueve (int pos, int mov){
		int toReturn = -1;
		switch (mov){
			case 0:
				toReturn = pos-5;
				break;
			case 1:
				toReturn = pos+1;
				break;
			case 2: 
				toReturn = pos+5;
				break;
			case 3:
				toReturn = pos-1;
				break;
		}
		return toReturn;
	}
	
	//Devuelve true si es posible hacer un movimiento y false en caso contrario
	bool posibleMov (Board t, int pos, int mov){
		return !((pos<4 && mov==0) || (pos>20 && mov==2) ||
			(pos==24 && mov==1) || (pos==0 && mov==3) ||
			(t.getPlayer(pos)!=0));
	}
	
	//Devuelve el tablero resultante tras efectuar un movimiento
	Board nuevoBoard (Board t, int pos, int mov){
		if(posibleMov(pos, mov)){
			int nuevapos = mueve(pos, mov);
			t.remove(pos);
			t.set(pos);
		}else{
			return t;
		}
	}
	
	//Devuelve el beneficio de un movimiento
	int beneficio (Board t, int pos, int mov){
		
	}
}