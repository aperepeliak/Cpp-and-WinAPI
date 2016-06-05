#pragma once
#include <Windows.h>

// добавил inline, иначе нарушаю One Definition Rule 
// (решение нашел здесь : http ://stackoverflow.com/questions/622229/error-lnk2005-already-defined-c)
//  как сделать без inline - не знаю

void inline SetCursorPosition(short x_position, short y_position) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD _coordPosition = { x_position, y_position };
	SetConsoleCursorPosition(hConsole, _coordPosition);
}

enum {
	clBlack, clNavy, clGreen, clTeal, clBrown,
	clPurple, clOlive, clGray, clSilver, clBlue,
	clLime, clCyan, clRed, clMagneta, clYellow,
	clWhite
};

void inline SetConsoleColorTextBackground(unsigned short Tex = clWhite, unsigned short Bg = clBlack)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Bg = Bg << 4 | Tex;
	SetConsoleTextAttribute(hConsole, Bg);
}

// —лужебные функции дл€ кубка
bool inline PowerOfTwo(int n) {
	// явл€етс€ ли n степенью 2
	if (n == 1)
		return true;
	if ((n % 2) == 0) {
		return PowerOfTwo(n / 2);
	}
	return false;
}
int inline NearestPowerOfTwo(int n, int two = 2) {
	if (n < two * 2) {
		return two;
	}
	else {
		return NearestPowerOfTwo(n, two * 2);
	}
}
int inline NumberOfTours(int n) {
	if (n == 1) {
		return 0;
	}
	return 1 + NumberOfTours(n / 2);
}