#pragma once
#include "Tournament.h"

class Cup :
	public Tournament
{
	void Schedule();	// Жеребьевка команд 
	void UserPlay(bool user_is_host, int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp);
	void ComputerPlay(int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp);

public:
	Cup(List_Clubs _teams);
	void PlayNextStage();
	void Show();
};