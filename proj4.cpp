#include <iostream>
using namespace std;

// Matthew Sanchez and Alexander Gomez
//
// CPSC 240
//

short a;
void base2()
{
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


//Q1 functions and declarations

short numPrinters, numFloppyDrives, sizeOfRam, b;

void displayAll() {
	cout << "The number of printers connected to the computer: " << numPrinters << endl;
	cout << "The number if floppy drives: " << numFloppyDrives << endl;
	cout << "The size of RAM: " << sizeOfRam << endl;
}

int main() {

	// Q1

	_asm {
		mov ax, 1100111010011100b;
		mov b, 0000000000001100;
		and b, ax;
		shr b, 2;
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


	return 0;
}