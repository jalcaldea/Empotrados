#include "Arduino.h"
#include "Board.h"

Board (){
	board = {{0,0,0,0,0},
			 {0,0,0,0,0},
			 {0,0,0,0,0},
			 {0,0,0,0,0},
			 {0,0,0,0,0}};
}

void set(int x, y, player){
	board[x][y] = player;
}

void remove (int x,y){
	board[x][y] = 0;
}

int getPlayer (int x, y){
	return board[x][y];
}

int[2][] getPositions (int player){
	int count = 0;
	int toReturn [2][];
	
	for (int x=0; x<5; x++){
		for (int y=0; y<5; y++){
			if (board[x][y] == player){
				toReturn[1][count] = x;
				toReturn[2][count] = y;
			}
		}
	}
	
	return toReturn;
}

void clearBoard (){
	board = {{0,0,0,0,0},
			 {0,0,0,0,0},
			 {0,0,0,0,0},
			 {0,0,0,0,0},
			 {0,0,0,0,0}};
}