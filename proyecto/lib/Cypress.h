#ifndef Cypress_h
#define Cypress_h

#include "Arduino.h"
#include "Wire.h"


#define GPIO 0x20
#define MEM 0x50

#define R_GPORT0 0x00
#define W_GPORT0 0x08
#define INT_0 0x10

#define R_GPORT1 0x01
#define W_GPORT1 0x09
#define INT_1 0x11

#define R_GPORT2 0x02
#define W_GPORT2 0x0A
#define INT_2 0x12

#define R_GPORT3 0x03
#define W_GPORT3 0x0B
#define INT_3 0x13

#define R_GPORT4 0x04
#define W_GPORT4 0x0C
#define INT_4 0x14

#define R_GPORT5 0x05
#define W_GPORT5 0x0D
#define INT_5 0x15

#define R_GPORT6 0x06
#define W_GPORT6 0x0E
#define INT_6 0x16

#define R_GPORT7 0x07
#define W_GPORT7 0x0F
#define INT_7 0x17

#define ENABLER 0x2D

#define PASS1 0x43
#define PASS2 0x4D
#define PASS3 0x53

#define VALUE 0x02

#define LASTDIR 27647
#define NULL 0xF2

#define STATUS 0x2E


class Cypress{
	public:
		static int turnUpEEPROM();
		static int save(unsigned int dir, byte data);
		static int saveData(unsigned int dir, byte* data);
		static byte read(unsigned int dir);
		static void readData(unsigned int dir,byte* rdata, int len);
		static byte readReg(byte reg);
		static void readRegData(byte reg,byte* rdata, int len);
		static int writeReg(byte reg, byte val);
};

#endif
