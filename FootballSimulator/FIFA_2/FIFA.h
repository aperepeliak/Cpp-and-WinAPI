#pragma once
#include "Tournament.h"

using namespace std;

class FIFA
{
	int num_leagues;							// ���������� ���
	int difficulty;								// ������� ���������
	List_Clubs* leagues;						// ����, ����������� � ����
	Tournament** game;							// ��� ���������� �������

	void LoadLeagues();							// �������� ���� ��� � ���������
	void Chooseleague();						// ������ ���� userLeague ��������� ���� �� true 
	void ChooseClub(int i);						// ������ ���� userClub ��������� ������� �� true
	void ChooseDifficulty();					// ���������� ������� ��������� ���� ��� ������������
	int FindChosenLeague();						// ��� ������ �����
	
	void StartMenu();							// ��������� ���� ��� ������ ������������ ���� � �������	
	void CreateTournaments();					// ����� �������� ���� ���, ������� �������

	void BrowseMenu(int option = 0);			// ��� ��������� ������ ������ ��� ����� ������

public:
	FIFA();
	void Play();								// ������ ���� ��� ���� �������� (� ���������� - ��� ���, � ����� - ���� 1/n ������)
	~FIFA();
};

