#ifndef Board_h
#define Board_h

#include "Arduino.h"

class Board{
	private:
		byte Board[25];
		byte limit[4];
	public:
		Board ();
		void set(byte pos, player);
		void remove (byte pos);
		byte move (byte oldPos, byte newPos)
		byte getPlayer (byte pos);
		byte[] getPositions (byte player);
		void clearBoard ();
		void setLimits();
		bool blocked (byte pos);
		byte[4] Board::getLimits();
		Board copyBoard ();
		byte[2] parseMask (bool[25] mk);
		byte newPosition (byte pos, byte mov);
		byte[] actualize (bool[25] mk);
		//byte movement (byte pos1, pos2);
}

#endif