#include "Tournament.h"

Tournament::Tournament(List_Clubs _teams)
{
	teams = _teams;
	stage = 0;
	is_not_ended = true;

	RandomSeed();
}

void Tournament::RandomSeed() {
	int num_teams = teams.getNumTeams();
	int* mas = new int[num_teams];
	for (int i = 0; i < num_teams; i++) {
		mas[i] = i;
	}
	int temp, r;
	for (int i = 0; i < num_teams; i++) {
		r = rand() % (num_teams - i) + i;
		temp = mas[i];
		mas[i] = mas[r];
		mas[r] = temp;
	}
	for (int i = 0; i < num_teams; i++) {
		Club* ptr = teams.ClubPos(i);
		ptr->setSeedNum(mas[i]);
	}
	delete[]mas;
}

bool Tournament::TournamentNotEnded()
{
	return is_not_ended;
}

string Tournament::getLeagueName() {
	return teams.getLeagueName();
}

bool Tournament::UserLeague() {
	return teams.getUserLeague();
}
