#include "Arduino.h"
#include "Board.h"

//Los límites se marcarán con el valor 9

Board::Board (){
	board = {0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0};
	 limit = {1, 5, 6, 10}
}

void Board::set(byte pos, player){
	board[pos] = player;
}

void Board::remove (byte pos){
	board[pos] = 0;
}

//Devuelve -1 si el movimiento no es válido
byte Board::move (byte oldPos, byte newPos){
	if(board[oldPos]==9 || board[oldPos]==0 || board[newPos]!==0){
		return -1;
	}else{
		this.set(newPos, board[oldPos]);
		this.remove(oldPos);
	}
}

byte Board::getPlayer (byte pos){
	return board[pos];
}

byte[] Board::getPositions (byte player){
	byte count = 0;
	byte toReturn [];
	
	for (byte x=0; x<25; x++){
		if (board[x] == player){
			toReturn[count] = x;
			count++;
		}
	}
	
	return toReturn;
}

void Board::clearBoard (){
	board = {0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0};
}

bool Board::blocked (byte p){
	return ((p<5 || p-5!=0 || p-5==9) && (p>19 || p+5!=0 || p+5==9) && (p%5=0 || p-1!=0 || p-1==9) && (p%5=4 || p+1!=0 || p+1==9))
}

void Board::setLimits(){
	byte count = 1;
	bool found = false;
	
	//Filas desde arriba
	while(!found){
			
		byte ini = count*5;
		for(byte i=ini; i<ini+5 && !found; i++){
			found = (board[i] != 0 && board[i] != 9);
		}
		if(!found){
			count++;
			for(byte i=ini; i<ini+5 && !found; i++){
				board[i] = 9;
			}
		}
		limit[0] = count;
	}
	
	count = 5;
	found = false;
	//Filas desde abajo
	while(!found){
		count--;
		
		byte ini = count*5;
		for(byte i=ini; i<ini+5 && !found; i++){
			found = (board[i] != 0 && board[i] != 9);
		}
		if(!found){
			
			for(byte i=ini; i<ini+5 && !found; i++){
				board[i] = 9;
			}
		}
		limit[1] = count;
	}
	
	count = 1;
	found = false;
	//Columnas desde izda
	while(!found){
			
		byte ini = count-1;
		for(byte i=ini; i<ini+20 && !found; i+=5){
			found = (board[i] != 0 && board[i] != 9);
		}
		if(!found){
			count++;
			for(byte i=ini; i<ini+20 && !found; i+=5){
				board[i] = 9;
			}
		}
		limit[2] = count;
	}
	
	count = 5;
	found = false;
	//Columnas desde la drcha
	while(!found){
		count--;
		
		byte ini = count-1;
		for(byte i=ini; i<ini+20 && !found; i+=5){
			found = (board[i] != 0 && board[i] != 9);
		}
		if(!found){
			
			for(byte i=ini; i<ini+20 && !found; i+=5){
				board[i] = 9;
			}
		}
	}
	limit[3] = count;
	
}

byte[4] Board::getLimits(){
	return limit;
}

Board Board::copyBoard (){
	Board toReturn = new Board();
	for (byte i=0; i<25; i++){
		toReturn.set(i, board[i]);
	}
	
	return toReturn;
}

//Devuelve la posición inicial y final dada una máscara.
//En caso de movimiento no válido devuelve -1 en ambas
byte[2] Board::parseMask (bool[25] mk){
	/*Si viene en forma de byte añadir este bucle:
	Tan solo transforma un byte a un byte[]
	
	byte[25] mk;
	byte byte; 
	byte counter = 0;
 
	for(t=128; t>0; t = t/2){
		if(byte & t) mk[counter]=1; 
		else mk[counter]=1; 
		counter++;
	}
	*/
	
	bool err = false;
	byte pos1 = -1;
	byte pos2 = -1;
	for (byte i=0; i<25 && !err; i++){
		if(mk[i]){
			if(board[i]==9){
				err = true;
			}else if(board[i]==0){
				if(pos2!=-1){
					pos2 = i;
				}else{
					err = true;
				}
			}else{
				if(pos1!=-1){
					pos1 = i;
				}else{
					err = true;
				}
			}
		}
	}
	if (pos1==-1 || pos2==-1){
		byte toReturn[2] = {-1, -1};
		return toReturn;
	}else{
		byte toReturn[2] = {pos1, pos2};
		return toReturn;
	}
}

//Devuelve la nueva posición si efectuas un movimiento. 
//En caso de no ser válido devuelve -1
byte Board::newPosition (byte pos, byte mov){
	if((board[pos]==0) || (board[pos]==9) ||
	 (mov==0 && pos<5) || (mov==1 && pos%5==4) || 
	 (mov==2 && pos>19) || (mov==3 && pos%5==0)){
	   return -1;
   }else{
	   byte np = -1;
	   switch (mov){
		case 0:
			np = pos-5;
			break;
		case 1:
			np = pos+1;
			break;
		case 2:
			np = pos+5;
			break;
		case 3:
			np = pos-5;
			break;
		default:
			return -1;
		
	   }
   }
   
   if(board[np]!=0 && board[np]!=9){
	   return np;
   }else{
	   return -1;
   }
}

//Realiza un movimiento y actualiza el tablero. Devuelve las fichas comidas
byte[] Board::actualize (bool[25] mk){
	
	//Realiza el movimiento
	byte[2] poss = parseMask(mk);
	move(poss[0], poss[1]);
	
	//Comprueba los límites
	board.setLimits();
	
	//Analiza las comidas
	byte counter = 0;
	byte toReturn[];
	for(byte i=0; i<25; i++){
		if(aux.getPlayer(i)!=9 && aux.getPlayer(i)!=0){
			toReturn[counter]=aux.getPlayer(i);
			counter++;
			t.remove(i);
	}
	
	//Devuelve las comidas
	return toReturn;
}