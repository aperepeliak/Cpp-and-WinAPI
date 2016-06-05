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

	int num_teams;			// Количество команд в лиге	
	string leagueName;		// Название лиги
	bool userLeague;		// Лига, в которой играет команда пользователя - true;

public:
	List_Clubs();
	List_Clubs(string n);

	void setLeagueName(string league_n);
	void setUserLeague(bool f);

	int getNumTeams();
	string getLeagueName();
	bool getUserLeague();

	List_Clubs(const List_Clubs& obj);						// Конструктор копий
	List_Clubs& operator = (const List_Clubs& obj);			// Перегрузка оператора присвоения
	
	void Pushback(string n, int stren);						// Добавление клуба
	void Pushback(string n, int stren, bool userCl);		// Добавление клуба
	void Popend();											// Удаление (для деструктора)
	void Sort();											// Сортировка по количеству очков, а затем по разнице забитых и пропущенных мячей
	void ShowTable();										// Вывод обычной таблицы чемпионата на экран
	void ShowTempoTable();									// Таблица-градусник

	Club* ClubInfo(int seed);								// Для обновления / получения данных команды по сеянному номеру
	Club* ClubPos(int pos);									// Для обновления / получения данных команды по порядковому номеру
	
	~List_Clubs();
};

