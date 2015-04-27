#ifndef Board_h
#define Board_h

#include "Arduino.h"

#define NIL 200


class Board{
	private:
		byte board[25];
		byte limit[4];
		byte poss[2];
		byte eliminated[9] = {NIL,NIL,NIL,NIL,NIL,NIL,NIL,NIL,NIL};
	public:
		Board ();
		void checkLimits();
		void set(byte pos, byte player);
		bool move (byte pos, byte mov, byte jug);
		byte getPlayer (byte pos);
		byte getPositions (byte player);
		byte getPosition (byte player,byte (&cas)[3]);
		void clearBoard ();
		bool blocked (byte pos);
		byte* getLimits();
		byte* copyBoard ();
		void parseMask (bool mk[25], byte jug, bool inicial);
		byte newPosition (byte pos, byte mov,byte jug);
		bool actualize (bool mk[25], byte jug, bool inicial);
		void remove (byte pos);
		void getEliminated(byte (&elim)[9]);
		void comer(bool inicial);
		//byte movement (byte pos1, pos2);
};

#endif
