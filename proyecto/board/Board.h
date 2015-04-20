#ifndef Board_h
#define Board_h

#include "Arduino.h"

class Board{
	private:
		int[25] Board;
		int limitX=0;
		int limitY=0;
	public:
		Board ();
		void set(int pos, player);
		void remove (int pos);
		int getPlayer (int pos);
		int getPositions (int player);
		void clearBoard ();
		void setLimits();
		bool blocked (int pos);
		Board copyBoard ();
}

#endif