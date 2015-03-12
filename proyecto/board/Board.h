#ifndef Board_h
#define Board_h

#include "Arduino.h"

class Board{
	private:
		int[5][5] Board;
	public:
		Board ();
		void set(int x, y, player);
		void remove (int x,y);
		int getPlayer (int x, y);
		int getPositions (int player);
		void clearBoard ();
}

#endif