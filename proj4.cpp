#include <iostream>
using namespace std;

// Matthew Sanchez and Alexander Gomez
//
// CPSC 240
//

short a;
void base2()
{
	cout << "AX = ";
	short   x = 1 << 15, t, n = a;
	for (int i = 1; i <= 16; ++i)
	{
		t = n & x;
		if (t == 0)
		{
			cout << 0;
		}
		else
		{
			cout << 1;
		}
		if (i % 4 == 0)
		{
			cout << " ";
		}
		n = n << 1;
	}
	a = n; // save the original value of a 
	cout << endl;
}


// Q1 functions and declarations

short numPrinters, numFloppyDrives, sizeOfRam, b;
void displayAll() {
	cout << "The number of printers connected to the computer: " << numPrinters << endl;
	cout << "The number if floppy drives: " << numFloppyDrives << endl;
	cout << "The size of RAM: " << sizeOfRam << endl;
}


// Q2 functions and declarations

short temp;
void beefIsValid() {
	cout << "BEEF is a valid ID for the family" << endl;
}
void beefNotValid() {
	cout << "BEEF is not a valid ID for the family" << endl;
}
void fadeIsValid() {
	cout << "FADE is a valid ID for the family" << endl;
}
void fadeNotValid() {
	cout << "FADE is not a valid ID for the family" << endl;
}
void cabeIsValid() {
	cout << "CABE is a valid ID for the family" << endl;
}
void cabeNotValid() {
	cout << "CABE is not a valid ID for the family" << endl;
}

// Q3 functions and declarations

short sprinklerCounter = 0, moveCounter = 0, maxMoves = 16, currentSprinkler = 17;
void displayNumSprinklers() {
	cout << sprinklerCounter << " sprinklers are ON" << endl;
}
void defectiveSprinklersSetup() {
	cout << "Defective sprinklers: ";
}
void displayCurrentSprinkler() {
	cout << currentSprinkler << " ";
}

// Q4 functions and declarations

short currentFloor = 17;
void elevatorSetup() {
	cout << "Elevator will stop at floors no. ";
}
void displayCurrentFloor() {
	cout << currentFloor << " ";
}


int main() {

	// Q1

	_asm {
		mov ax, 1100111010011100b;
		mov b, 0000000000001100;		// put in this binary to check bits 3 & 4
		and b, ax;						// compares bits 3 and 4
		shr b, 2;						// moves out come to the right to compare
		cmp b, 0;
		Je ram16;
		cmp b, 1;
		Je ram32;
		cmp b, 2;
		Je ram48;
		cmp b, 3;
		Je ram64;
	ram16:
		mov sizeOfRam, 16;
		Jmp step2;
	ram32:
		mov sizeOfRam, 32;
		Jmp step2;
	ram48:
		mov sizeOfRam, 48;
		Jmp step2;
	ram64:
		mov sizeOfRam, 64;
		Jmp step2;
	step2:
		mov b, 0000000011000000b;
		and b, ax;
		shr b, 6;
		cmp b, 0;
		Je oneDrive;
		cmp b, 1;
		Je twoDrives;
		cmp b, 2;
		Je threeDrives;
		cmp b, 3;
		Je fourDrives;
	oneDrive:
		mov numFloppyDrives, 1;
		Jmp step3;
	twoDrives:
		mov numFloppyDrives, 2;
		Jmp step3;
	threeDrives:
		mov numFloppyDrives, 3;
		Jmp step3;
	fourDrives:
		mov numFloppyDrives, 4;
		Jmp step3;
	step3:
		mov b, 1100000000000000b;
		and b, ax;
		shr b, 14;
		cmp b, 0;
		Je noPrinters;
		cmp b, 1;
		Je onePrinter;
		cmp b, 2;
		Je twoPrinters;
		cmp b, 3;
		Je threePrinters;
	noPrinters:
		mov numPrinters, 0;
		Jmp displayQ1;
	onePrinter:
		mov numPrinters, 1;
		Jmp displayQ1;
	twoPrinters:
		mov numPrinters, 2;
		Jmp displayQ1;
	threePrinters:
		mov numPrinters, 3;
		Jmp displayQ1;
	displayQ1:
		call displayAll;
	}

	cout << endl << endl;

	// Q2
	_asm {
		mov ax, 0xBEEF;
		mov temp, 0000000000000001b;
		and ax, temp;
		cmp ax, 0;
		Je validBeef;
		cmp ax, 1;
		Je notValidBeef;
	validBeef:
		call beefIsValid;
		Jmp checkFade;
	notValidBeef:
		call beefNotValid;
	checkFade:
		mov ax, 0;
		mov ax, 0xFADE;
		mov temp, 0000000000000001b;
		and ax, temp;
		cmp ax, 1;
		Je notValidFade;
		Jmp validFade;
	notValidFade:
		call fadeNotValid;
		Jmp checkCabe;
	validFade:
		call fadeIsValid;
	checkCabe:
		mov ax, 0;
		mov ax, 0xCABE;
		mov temp, 0000000000000001b;
		and ax, temp;
		cmp ax, 1;
		Je notValidCabe;
		Jmp validCabe;
	notValidCabe:
		call cabeNotValid;
		Jmp q2done;
	validCabe:
		call cabeIsValid;
	q2done:
	}

	cout << endl << endl;

	// Q3
	_asm {
		mov ax, 0110101000101111b;

		// display as binary
		mov a, ax;
		call base2;
		mov a, 0000000000000001b;
		
		// check if sprinklers are on
		mov bx, maxMoves;
	startLoopQ3:
		inc moveCounter;
		cmp bx, moveCounter;
		Je exitLoopQ3;
		mov ax, 0110101000101111b;
		and ax, a;
		cmp ax, 0;
		Jne increaseCounter;				// jump to increment sprinklerCounter by 1
		shl a, 1;							// if not just shift left and go again
		Jmp startLoopQ3;
	increaseCounter:
		inc sprinklerCounter;
		shl a, 1;
		Jmp startLoopQ3;
	exitLoopQ3:
		call displayNumSprinklers;
	// find defective sprinklers
		call defectiveSprinklersSetup;
		mov a, 1000000000000000b;
	startSecondLoopQ3:
		mov bx, 0;
		dec currentSprinkler;
		cmp bx, currentSprinkler;
		Je exitSecondLoopQ3;
		mov ax, 0110101000101111b;
		and ax, a;
		cmp ax, 0;
		Je isDefective;
		shr a, 1;
		Jmp startSecondLoopQ3;
	isDefective:
		call displayCurrentSprinkler;
		shr a, 1;
		Jmp startSecondLoopQ3;
	exitSecondLoopQ3:
	}

	cout << endl << endl;

	// Q4
	_asm {
		mov a, 1001000100001100b;
		call base2;
		call elevatorSetup;
		mov a, 1000000000000000b;
	startLoopQ4:
		dec currentFloor;
		mov bx, 0;
		cmp bx, currentFloor;
		Je exitLoopQ4;
		mov ax, 1001000100001100b;
		and ax, a;
		cmp ax, 0;
		Jne willStop;
		shr a, 1;
		Jmp startLoopQ4;
	willStop:
		call displayCurrentFloor;
		shr a, 1;
		Jmp startLoopQ4;
	exitLoopQ4:
	}

	cout << endl;


	return 0;
}