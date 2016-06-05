#pragma once
#include "Tournament.h"
#include "ServiceFunc.h"

class Champ :
	public Tournament
{
	void Schedule();					// ���������� ������ (����� ����������� � ����������� �� ���� �������)
	void UserPlay(bool user_is_host, int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp);
	void ComputerPlay(int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp);

public:

	Champ(List_Clubs _teams);
	void PlayNextStage();
	void Show();

};

