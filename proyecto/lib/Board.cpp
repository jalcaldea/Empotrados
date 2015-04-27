#include "Board.h"

//Los límites se marcarán con el valor 9

Board::Board (){
			 
	for(byte i=0;i<25;i++){
		board[i] = 0;
	}
			 
	 limit[0] = NIL;
	 limit[1] = NIL;
	 limit[2] = NIL;
	 limit[3] = NIL;
}

void Board::set(byte pos, byte player){
	board[pos] = player;
}

void Board::remove (byte pos){
	board[pos] = 0;
}

//Devuelve -1 si el movimiento no es válido
bool Board::move (byte pos, byte mov, byte jug){

	byte newPos = this->newPosition(pos,mov,jug);

	if(newPos==NIL){
		return false;
	}else{
		
		if(mov==4){
			this->set(newPos, jug);
		}else{				
			this->set(newPos, board[pos]);
			this->remove(pos);
		}

	}
	
	return true;
}

byte Board::getPlayer (byte pos){
	return board[pos];
}
byte Board::getPosition (byte player,byte (&cas)[3]){

	cas[0] = NIL;
	cas[1] = NIL;
	cas[2] = NIL;

	byte count = 0;
	
	for (byte x=0; x<25 && count<3 ; x++){
		if (board[x] == player){
			cas[count] = x;
			count++;
		}
	}
	
	return count;
}

byte Board::getPositions (byte player){
	byte count = 0;
	
	for (byte x=0; x<25 && count<3 ; x++){
		if (board[x] == player){
			count++;
		}
	}
	
	return count;
}

void Board::clearBoard (){
	Board();
}

bool Board::blocked (byte p){
	return ((p<5 || board[p-5]!=0 || board[p-5]==9) && (p>19 || board[p+5]!=0 || board[p+5]==9) && (p%5==0 || board[p-1]!=0 || board[p-1]==9) && (p%5==4 || board[p+1]!=0 || board[p+1]==9));
}

void Board::checkLimits(){
	byte pos = 0;
	bool found = false;
	
	
	while(!found || pos<25){
		found = found || (board[pos] != 0 && board[pos] != 9);
		
		if((pos % 5)==4 && !found){		
			board[pos-4] = 9;
			board[pos-3] = 9;
			board[pos-2] = 9;
			board[pos-1] = 9;
			board[pos] = 9;
			
			limit[0] = (pos/5)+1;
		}
		
		pos++;
	}
	
	pos = 24;
	found = false;
	
	while(!found || pos>0){
		found = found || (board[pos] != 0 && board[pos] != 9);
		
		if((pos % 5)==0 && !found){		
			board[pos+4] = 9;
			board[pos+3] = 9;
			board[pos+2] = 9;
			board[pos+1] = 9;
			board[pos] = 9;
			
			limit[2] = (pos/5)+1;
		}
		
		pos--;
	}
	
	pos = 0;
	found = false;
	
	while(!found || pos<25){
		found = found || (board[pos] != 0 && board[pos] != 9);
		
		if((pos >=20 ) && !found){		
			board[pos-20] = 9;
			board[pos-15] = 9;
			board[pos-10] = 9;
			board[pos-5] = 9;
			board[pos] = 9;
			
			limit[1] = (pos % 5)+6;
		}
		
		if(pos>=20 && pos<24){
			pos -= 19;			// Avanza una fila;
		}else{
			pos += 5;
		}
		
	}
	
	
	pos = 24;
	found = false;
	
	while(!found || pos>0){
		found = found || (board[pos] != 0 && board[pos] != 9);
		
		if((pos <=4 ) && !found){		
			board[pos+20] = 9;
			board[pos+15] = 9;
			board[pos+10] = 9;
			board[pos+5] = 9;
			board[pos] = 9;
			
			limit[3] = (pos % 5)+6;
		}
		
		if(pos<=4 && pos>0){
			pos += 19;			// Avanza una fila;
		}else{
			pos -= 5;
		}
		
	}
}

byte* Board::getLimits(){
	return limit;
}

byte* Board::copyBoard (){
	byte toReturn[25] = {};
	for (byte i=0; i<25; i++){
		toReturn[i] = board[i];
	}
	
	return toReturn;
}

//Devuelve la posición inicial y final dada una máscara.
//En caso de movimiento no válido devuelve -1 en ambas
void Board::parseMask (bool mk[25], byte jug, bool inicial){
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
	byte pos1 = NIL;
	byte pos2 = NIL;
	byte i = 0;
	while((pos2==NIL || (pos1==NIL && !inicial)) && !err && i<25){
	
		if(mk[i]){
		
			if(board[i]==9){
				err = true;
			}else if(board[i]==0){
			
				if(pos2==NIL){
					pos2 = i;
				}else{
					err = true;
				}
				
			}else{
				if(pos1==NIL){
					pos1 = i;
				}else{
					err = true;
				}
			}
		}
		
		i++;
	}
	
	byte mov = NIL;
	
	
	if(pos1==NIL && pos2 !=NIL && inicial){
		pos1 = pos2;
		mov = 4;
	}else if(board[pos1]==jug){
	
		if(pos2==(pos1 - 5)){
			mov = 0;
		}else if(pos2== (pos1 + 1)){
			mov = 1;
		}else if(pos2== (pos1 + 5)){
			mov = 2;
		}else if(pos2== (pos1 - 1)){
			mov = 3;
		}else{
			pos1 = NIL;
			pos2 = NIL;
		}
	}
	
	
	poss[0] = pos1;
	poss[1] = mov;
}

//Devuelve la nueva posición si efectuas un movimiento. 
//En caso de no ser válido devuelve -1
byte Board::newPosition (byte pos, byte mov, byte jug){

	byte newPos = NIL;
	
	if(pos==NIL || mov==NIL){
		return NIL;
	}
	
	if(!( ((board[pos]!=0) && (board[pos]!=jug)) || (board[pos]==9) ||
	 (mov==0 && pos<5) || (mov==1 && pos%5==4) || 
	 (mov==2 && pos>19) || (mov==3 && pos%5==0)) ){
	   switch (mov){
		case 0:
			newPos = pos-5;			
			break;
		case 1:
			newPos = pos+1;
			break;
		case 2:
			newPos = pos+5;
			break;
		case 3:
			newPos = pos-1;
			break;
		case 4:
			newPos = pos;
			break;
		
	   }
	}
	   
	if(newPos>=25 || board[newPos]!=0){
		newPos = NIL;
	}
	      
	 return newPos;
}


//Realiza un movimiento y actualiza el tablero. Devuelve las fichas comidas
bool Board::actualize (bool mk[25], byte jug, bool inicial){
	
	
	
	poss[0] = NIL;
	poss[1] = NIL;
	//Realiza el movimiento
	parseMask(mk, jug, inicial);
	

	if(move(poss[0], poss[1], jug)){
	
	
		if(!inicial){
			//Comprueba los límites
			this->checkLimits();
		}
		
		
		
		byte aux[9] ={};
		
		getEliminated(aux);
		
		return true;
	}else{
		return false;
	}
	//Devuelve las comidas
}

void Board::comer(bool inicial){
	
	remove(eliminated[0]);

	eliminated[0] = eliminated[1];
	eliminated[1] = eliminated[2];
	eliminated[2] = eliminated[3];
	eliminated[3] = eliminated[4];
	eliminated[4] = eliminated[5];
	eliminated[5] = eliminated[6];
	eliminated[6] = eliminated[7];
	eliminated[7] = NIL;
	
	if(!inicial){
		checkLimits();
	}
	byte aux[9] ={};
		
		getEliminated(aux);
}

void Board::getEliminated(byte (&elim)[9]){
	//Analiza las comidas
	byte counter = 0;

	for(byte i=0; i<25; i++){
			if(board[i]!=9 && board[i]!=0){
				if(this->blocked(i)){
					eliminated[counter] = i;
					counter++;
				}
			}
		}

	elim[0] = eliminated[0];
	elim[1] = eliminated[1];
	elim[2] = eliminated[2];
	elim[3] = eliminated[3];
	elim[4] = eliminated[4];
	elim[5] = eliminated[5];
	elim[6] = eliminated[6];
	elim[7] = eliminated[7];
	elim[8] = eliminated[8];
}
