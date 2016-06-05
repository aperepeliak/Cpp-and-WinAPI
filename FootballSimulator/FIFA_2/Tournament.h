#pragma once
#include "List_Clubs.h"
#include "List_Matches.h"

class Tournament
{
protected:
	List_Clubs teams;
	List_Matches matches;
	int stage;
	bool is_not_ended;

	virtual void Schedule() = 0;		// Жеребьевка команд (будет различаться в зависимости от типа турнира)
	void RandomSeed();					// Случайный посев команд
	virtual void UserPlay(bool user_is_host,int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp) = 0;
	virtual void ComputerPlay(int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp) = 0;

public:
	Tournament(List_Clubs _teams);

	string getLeagueName();
	bool UserLeague();
	bool TournamentNotEnded();										// Проверка завершения турнира (например, сыграны ли все туры / сыгран ли финал)
	
	virtual void PlayNextStage() = 0;								// Проведение следующего этапа турнира
	virtual void Show() = 0;
	virtual~Tournament() = 0;
};

inline Tournament::~Tournament() {}
