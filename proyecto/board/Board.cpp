#include "Arduino.h"
#include "Board.h"

Board (){
	board = {0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0};
}

void set(int pos, player){
	board[pos] = player;
}

void remove (int pos){
	board[pos] = 0;
}

int getPlayer (int pos){
	return board[pos];
}

int[] getPositions (int player){
	int count = 0;
	int toReturn [];
	
	for (int x=0; x<25; x++){
		if (board[x] == player){
			toReturn[count] = x;
			count++;
		}
	}
	
	return toReturn;
}

void clearBoard (){
	board = {0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0,
			 0,0,0,0,0};
}

bool blocked (int pos){
	
}

void setLimits(){
	
}

Board copyBoard (){
	
}