#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Club.h"

using namespace std;

class List_Clubs
{
	class Node : public Club {
		Node* prev;
		Node* next;

	public:
		Node(string n, int stren) : Club(n, stren) { prev = nullptr; next = nullptr; }
		Node(string n, int stren, bool userCl) : Club(n, stren, userCl) { prev = nullptr; next = nullptr; }
		void setNext(Node* n) { next = n; }
		void setPrev(Node* p) { prev = p; }
		Node* getNext() { return next; }
		Node* getPrev() { return prev; }
		Node* getClubInfo() { return this; }
	};

	Node* start;
	Node* end;

	int num_teams;			// ���������� ������ � ����	
	string leagueName;		// �������� ����
	bool userLeague;		// ����, � ������� ������ ������� ������������ - true;

public:
	List_Clubs();
	List_Clubs(string n);

	void setLeagueName(string league_n);
	void setUserLeague(bool f);

	int getNumTeams();
	string getLeagueName();
	bool getUserLeague();

	List_Clubs(const List_Clubs& obj);						// ����������� �����
	List_Clubs& operator = (const List_Clubs& obj);			// ���������� ��������� ����������
	
	void Pushback(string n, int stren);						// ���������� �����
	void Pushback(string n, int stren, bool userCl);		// ���������� �����
	void Popend();											// �������� (��� �����������)
	void Sort();											// ���������� �� ���������� �����, � ����� �� ������� ������� � ����������� �����
	void ShowTable();										// ����� ������� ������� ���������� �� �����
	void ShowTempoTable();									// �������-���������

	Club* ClubInfo(int seed);								// ��� ���������� / ��������� ������ ������� �� �������� ������
	Club* ClubPos(int pos);									// ��� ���������� / ��������� ������ ������� �� ����������� ������
	
	~List_Clubs();
};

