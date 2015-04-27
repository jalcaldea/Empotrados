#ifndef IA_h
#define IA_h

#include "Arduino.h"
#include "Board.h"


class IA{

	public:
		static void movimiento (Board t, byte jugador,byte (&pos)[2]);
		static bool posibleMov (Board t, byte pos, byte mov,byte jug);
		static Board nuevoBoard (Board t, byte pos, byte mov,byte jugador);
		static int beneficio (Board t, byte pos, byte mov, byte jugador, int& nuestro, byte siguiente,byte prof);
		static int movimientoajeno (Board t, byte jugador, int& nuestro, byte siguiente,byte prof);
		//byte movement (byte pos1, pos2);
};

#endif

