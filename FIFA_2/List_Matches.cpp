#include <iostream>
#include "List_Matches.h"
#include "ServiceFunc.h"

using namespace std;

List_Matches::List_Matches()
{
	num_matches = 0;
	start = end = nullptr;
}

List_Matches::List_Matches(const List_Matches& obj)
{
	start = end = nullptr;
	num_matches = 0;
	Node* cur = obj.start;
	while (cur) {
		Pushback(cur->getHost(), cur->getGuest(), cur->getTour(), cur->getRound());
		cur = cur->getNext();
	}
}

List_Matches& List_Matches::operator = (const List_Matches& obj)
{
	if (this == &obj)
		return *this;
	while (num_matches)
		Popend();
	Node* cur = obj.start;
	while (cur) {
		Pushback(cur->getHost(), cur->getGuest(), cur->getTour(), cur->getRound());
		cur = cur->getNext();
	}
	return *this;
}

void List_Matches::Pushback(int h, int g, int t, int r)
{
	Node* tmp = new Node(h, g, t, r);
	if (num_matches == 0) {
		start = end = tmp;
		num_matches++;
	}
	else {
		end->setNext(tmp);
		tmp->setPrev(end);
		end = tmp;
		num_matches++;
	}
}

void List_Matches::Popend()
{
	if (num_matches == 0) {
		return;
	}
	if (num_matches == 1) {
		start = end = nullptr;
		num_matches = 0;
		return;
	}
	Node* tmp = start;
	start = start->getNext();
	start->setPrev(nullptr);
	delete tmp;
	num_matches--;
}

void List_Matches::Show()
{
	// Координаты для отображения в консоли
	int init_y = 13;
	int y = init_y;
	int x = 5;
	int stepX = 30;
	int stepY = 5;
	int goals_pos = 18;

	if (PowerOfTwo(num_matches + 1)) {
		// Если количество команд является степенью 2
		int tours = NumberOfTours(num_matches + 1);
		int games = (num_matches + 1) / 2;
		Node* cur = start;

		for (int i = 0; i < tours; i++) {

			for (int j = 0; j < games; j++) {
				SetCursorPosition(x, y);
				if ((cur->getHostName()) != "undefined") {
					cout << cur->getHostName();
					SetCursorPosition(x + goals_pos, y);
					cout << cur->getHostScore();
					if (cur->getHostScore() == cur->getGuestScore()) {
						cout << " (" << cur->getHostPenalty() << ")";
					}
				}
				else {
					cout << " ";
				}
				SetCursorPosition(x, y + 1);
				cout << "-----------------------";
				SetCursorPosition(x, y + 2);
				if ((cur->getGuestName()) != "undefined") {
					cout << cur->getGuestName();
					SetCursorPosition(x + goals_pos, y + 2);
					cout << cur->getGuestScore();
					if (cur->getGuestScore() == cur->getHostScore()) {
						cout << " (" << cur->getGuestPenalty() << ")";
					}
				}
				else {
					cout << " ";
				}
				y += stepY;
				cur = cur->getNext();
			}
			y = init_y;
			x += stepX;
			games /= 2;
		}
	}
	else {
		// Если количество команд НЕ является степенью 2
		int tours = NumberOfTours(num_matches + 1) + 1;
		int games = NearestPowerOfTwo(num_matches + 1) / 2;
		Node* cur = start;

		for (int i = 0; i < tours; i++) {
			if (i == 0) {
				// Если первый тур
				for (int j = 0; j < ((num_matches + 1) - NearestPowerOfTwo(num_matches + 1)); j++) {
					SetCursorPosition(x, y);
					if ((cur->getHostName()) != "undefined") {
						cout << cur->getHostName();
						SetCursorPosition(x + goals_pos, y);
						cout << cur->getHostScore();
						if (cur->getHostScore() == cur->getGuestScore()) {
							cout << " (" << cur->getHostPenalty() << ")";
						}
					}
					else {
						cout << " ";
					}
					SetCursorPosition(x, y + 1);
					cout << "-----------------------";
					SetCursorPosition(x, y + 2);
					if ((cur->getGuestName()) != "undefined") {
						cout << cur->getGuestName();
						SetCursorPosition(x + goals_pos, y + 2);
						cout << cur->getGuestScore();
						if (cur->getGuestScore() == cur->getHostScore()) {
							cout << " (" << cur->getGuestPenalty() << ")";
						}
					}
					else {
						cout << " ";
					}
					y += stepY;
					cur = cur->getNext();
				}
				y = init_y;
				x += stepX;
			}
			else {
				// Если не первый тур
				for (int j = 0; j < games; j++) {
					SetCursorPosition(x, y);
					if ((cur->getHostName()) != "undefined") {
						cout << cur->getHostName();
						SetCursorPosition(x + goals_pos, y);
						cout << cur->getHostScore();
						if (cur->getHostScore() == cur->getGuestScore()) {
							cout << " (" << cur->getHostPenalty() << ")";
						}
					}
					else {
						cout << " ";
					}
					SetCursorPosition(x, y + 1);
					cout << "-----------------------";
					SetCursorPosition(x, y + 2);
					if ((cur->getGuestName()) != "undefined") {
						cout << cur->getGuestName();
						SetCursorPosition(x + goals_pos, y + 2);
						cout << cur->getGuestScore();
						if (cur->getGuestScore() == cur->getHostScore()) {
							cout << " (" << cur->getGuestPenalty() << ")";
						}
					}
					else {
						cout << " ";
					}
					y += stepY;
					cur = cur->getNext();
				}
				y = init_y;
				x += stepX;
				games /= 2;
			}
		}
	}
}

Match* List_Matches::MatchInfo(int round, int tour, int game)
{
	Node* cur = start;
	while (cur->getRound() != round) {
		cur = cur->getNext();
	}
	while (cur->getRound() == round) {
		while (cur->getTour() != tour) {
			cur = cur->getNext();
		}
		while (cur->getTour() == tour) {
			int count = 0;
			while (count != game) {
				cur = cur->getNext();
				count++;
			}
			return cur->getMatchInfo();
		}
	}
	return nullptr;
}
