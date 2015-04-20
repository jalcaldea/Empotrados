#ifndef Board_h
#define Board_h

#include "Arduino.h"

class Board{
	private:
		int Board[25];
		int limit[4];
	public:
		Board ();
		void set(int pos, player);
		void remove (int pos);
		int move (int oldPos, int newPos)
		int getPlayer (int pos);
		int[] getPositions (int player);
		void clearBoard ();
		void setLimits();
		bool blocked (int pos);
		int[4] Board::getLimits();
		Board copyBoard ();
		int[2] parseMask (int[25] mk);
		int newPosition (int pos, int mov);
		int[] actualize (int[25] mk);
		//int movement (int pos1, pos2);
}

#endif