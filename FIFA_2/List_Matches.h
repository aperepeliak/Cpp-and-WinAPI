#pragma once
#include "Match.h"

class List_Matches
{
	class Node : public Match {
		Node* prev;
		Node* next;
	public:
		Node(int h, int g, int t, int r = 0) : Match(h, g, t, r) { prev = nullptr; next = nullptr; }
		void setNext(Node* n) { next = n; }
		void setPrev(Node* p) { prev = p; }
		Node* getNext() { return next; }
		Node* getPrev() { return prev; }
		Node* getMatchInfo() { return this; }
	};

	Node* start;
	Node* end;
	int num_matches;		// Количество матчей в турнире

public:
	List_Matches();
	List_Matches(const List_Matches& obj);
	List_Matches& operator = (const List_Matches& obj);

	int getNumMatches(){ return num_matches; }
	void Pushback(int h, int g, int t, int r = 0);
	void Popend();
	void Show();
	Match* MatchInfo(int round, int tour, int game);

	~List_Matches() { while (num_matches) Popend(); }
};