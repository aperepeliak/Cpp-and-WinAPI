#include <iostream>
#include "Club.h"
#include "ServiceFunc.h"

using namespace std;

Club::Club(string n, int stren)
{
	name = n;
	strength = stren;
	userClub = false;
	seed_num = -1;
	points = 0;
	goals_scored = 0;
	goals_missed = 0;
	wins = 0;
	draws = 0;
	losses = 0;
}

Club::Club(string n, int stren, bool userCl) {
	name = n;
	strength = stren;
	userClub = userCl;
	seed_num = -1;
	points = 0;
	goals_scored = 0;
	goals_missed = 0;
	wins = 0;
	draws = 0;
	losses = 0;
}

void Club::AddToSeries(int h_sc, int g_sc) {
	series.push_back(Match(h_sc, g_sc));
}

void Club::ShowSeries(int num_games) {
	int k = 0;
	for (auto i = series.begin(); i < series.end(); i++, k++) {
		if (i->getHostScore()>i->getGuestScore()) {
			SetConsoleColorTextBackground(clGreen, clGreen);
			cout << "*" << ends;
			SetConsoleColorTextBackground(clBlack, clWhite);
		}
		else if (i->getHostScore() < i->getGuestScore()) {
			SetConsoleColorTextBackground(clRed, clRed);
			cout << "*" << ends;
			SetConsoleColorTextBackground(clBlack, clWhite);
		}
		else {
			SetConsoleColorTextBackground(clYellow, clYellow);
			cout << "*" << ends;
			SetConsoleColorTextBackground(clBlack, clWhite);
		}
	}
	for (int i = k; i < num_games; i++) {
		SetConsoleColorTextBackground(clGray, clGray);
		cout << "*" << ends;
		SetConsoleColorTextBackground(clBlack, clWhite);
	}
}
