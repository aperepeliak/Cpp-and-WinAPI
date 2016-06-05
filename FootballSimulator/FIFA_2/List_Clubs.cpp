#include "List_Clubs.h"
#include "ServiceFunc.h"

using namespace std;

List_Clubs::List_Clubs() {
	num_teams = 0;
	userLeague = false;
	start = end = nullptr;
}

List_Clubs::List_Clubs(string n)
{
	leagueName = n;
	num_teams = 0;
	userLeague = false;
	start = end = nullptr;
}

void List_Clubs::setLeagueName(string league_n)
{
	leagueName = league_n;
}

void List_Clubs::setUserLeague(bool f)
{
	userLeague = f;
}

int List_Clubs::getNumTeams()
{
	return num_teams;
}

string List_Clubs::getLeagueName() {
	return leagueName;
}

bool List_Clubs::getUserLeague()
{
	return userLeague;
}

List_Clubs::List_Clubs(const List_Clubs& obj) {
	start = end = nullptr;
	num_teams = 0;
	leagueName = obj.leagueName;
	userLeague = obj.userLeague;
	Node* cur = obj.start;
	while (cur) {
		Pushback(cur->getName(), cur->getStrength(), cur->getUserClub());
		cur = cur->getNext();
	}
}

List_Clubs& List_Clubs::operator = (const List_Clubs& obj) {
	if (this == &obj)
		return *this;
	while (num_teams)
		Popend();
	leagueName = obj.leagueName;
	userLeague = obj.userLeague;
	Node* cur = obj.start;
	while (cur) {
		Pushback(cur->getName(), cur->getStrength(), cur->getUserClub());
		cur = cur->getNext();
	}
	return *this;
}

void List_Clubs::Pushback(string n, int stren) {
	Node* tmp = new Node(n, stren);
	if (num_teams == 0) {
		start = end = tmp;
		num_teams++;
	}
	else {
		end->setNext(tmp);
		tmp->setPrev(end);
		end = tmp;
		num_teams++;
	}
}

void List_Clubs::Pushback(string n, int stren, bool userCl) {
	Node* tmp = new Node(n, stren, userCl);
	if (num_teams == 0) {
		start = end = tmp;
		num_teams++;
	}
	else {
		end->setNext(tmp);
		tmp->setPrev(end);
		end = tmp;
		num_teams++;
	}
}

void List_Clubs::Popend() {
	if (num_teams == 0) {
		return;
	}
	if (num_teams == 1) {
		start = end = nullptr;
		num_teams = 0;
		return;
	}
	Node* tmp = start;
	start = start->getNext();
	start->setPrev(nullptr);
	delete tmp;
	num_teams--;
}

void List_Clubs::Sort() {
	// Используется пузырьковая сортировка, меняются местами не данные, а узлы
	Node *cur1, *cur2;
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		cur1 = start;
		cur2 = start->getNext();
		while (cur2 != nullptr) {
			if (cur1->getPoints() < cur2->getPoints()) {
				swapped = 1;
				if (cur2->getNext() == nullptr) {
					cur1->getPrev()->setNext(cur2);
					cur2->setPrev(cur1->getPrev());
					cur2->setNext(cur1);
					cur1->setPrev(cur2);
					cur1->setNext(nullptr);
					end = cur1;
					cur2 = nullptr;
				}
				else if (cur1->getPrev() == nullptr) {
					cur1->setNext(cur2->getNext());
					cur2->getNext()->setPrev(cur1);
					cur2->setNext(cur1);
					cur1->setPrev(cur2);
					cur2->setPrev(nullptr);
					start = cur2;
					cur2 = cur1->getNext();
				}
				else {
					cur1->getPrev()->setNext(cur2);
					cur2->getNext()->setPrev(cur1);
					cur1->setNext(cur2->getNext());
					cur2->setPrev(cur1->getPrev());
					cur2->setNext(cur1);
					cur1->setPrev(cur2);
					cur2 = cur1->getNext();
				}
			}
			else if (cur1->getPoints() == cur2->getPoints()) {
				if ((cur1->getGoalsScored() - cur1->getGoalsMissed()) < (cur2->getGoalsScored() - cur2->getGoalsMissed())) {
					swapped = 1;
					if (cur2->getNext() == nullptr) {
						cur1->getPrev()->setNext(cur2);
						cur2->setPrev(cur1->getPrev());
						cur2->setNext(cur1);
						cur1->setPrev(cur2);
						cur1->setNext(nullptr);
						end = cur1;
						cur2 = nullptr;
					}
					else if (cur1->getPrev() == nullptr) {
						cur1->setNext(cur2->getNext());
						cur2->getNext()->setPrev(cur1);
						cur2->setNext(cur1);
						cur1->setPrev(cur2);
						cur2->setPrev(nullptr);
						start = cur2;
						cur2 = cur1->getNext();
					}
					else {
						cur1->getPrev()->setNext(cur2);
						cur2->getNext()->setPrev(cur1);
						cur1->setNext(cur2->getNext());
						cur2->setPrev(cur1->getPrev());
						cur2->setNext(cur1);
						cur1->setPrev(cur2);
						cur2 = cur1->getNext();
					}
				}
				else {
					cur1 = cur2;
					cur2 = cur1->getNext();
				}
			}
			else {
				cur1 = cur2;
				cur2 = cur1->getNext();
			}
		}
	}
}

void List_Clubs::ShowTable()
{
	Sort();
	Node* cur = start;
	int count = 1;

	// Переменные для координат столбцов
	int hor_pos = 15;
	int club_pos = 3;
	int wins_pos = 23;
	int draws_pos = 30;
	int loss_pos = 38;
	int sc_pos = 47;
	int miss_pos = 56;
	int points_pos = 65;

	cout << endl;
	cout << "#  |  Club             | Wins | Draws | Losses | Scored | Missed | Points" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	while (cur) {
		SetCursorPosition(0, hor_pos);
		cout << count;
		SetCursorPosition(club_pos, hor_pos);
		cout << "| " << cur->getName();
		SetCursorPosition(wins_pos, hor_pos);
		cout << "| " << cur->getWins();
		SetCursorPosition(draws_pos, hor_pos);
		cout << "| " << cur->getDraws();
		SetCursorPosition(loss_pos, hor_pos);
		cout << "| " << cur->getLosses();
		SetCursorPosition(sc_pos, hor_pos);
		cout << "| " << cur->getGoalsScored();
		SetCursorPosition(miss_pos, hor_pos);
		cout << "| " << cur->getGoalsMissed();
		SetCursorPosition(points_pos, hor_pos);
		cout << "| " << cur->getPoints();
		hor_pos++;
		count++;
		cur = cur->getNext();
	}
}

void List_Clubs::ShowTempoTable() {
	Sort();
	Node* cur = start;
	int count = 1;

	int hor_pos = 15;

	// Координаты стобцов
	int club_pos = 3;
	int series_pos = 24;
	int wins_pos = 2 + series_pos + 2 * ((num_teams * 2) - 2);
	int draws_pos = wins_pos + 7;
	int loss_pos = draws_pos + 8;
	int sc_pos = loss_pos + 8;
	int miss_pos = sc_pos + 9;
	int points_pos = miss_pos + 10;

	// Вывод на экран шапки таблицы
	SetCursorPosition(0, hor_pos - 2);
	cout << count;
	SetCursorPosition(club_pos, hor_pos - 2);
	cout << "| " << "Club";
	SetCursorPosition(series_pos, hor_pos - 2);
	cout << "| " << "Series";
	SetCursorPosition(wins_pos, hor_pos - 2);
	cout << "| " << "Wins";
	SetCursorPosition(draws_pos, hor_pos - 2);
	cout << "| " << "Draws";
	SetCursorPosition(loss_pos, hor_pos - 2);
	cout << "| " << "Losses";
	SetCursorPosition(sc_pos, hor_pos - 2);
	cout << "| " << "Scored";
	SetCursorPosition(miss_pos, hor_pos - 2);
	cout << "| " << "Missed";
	SetCursorPosition(points_pos, hor_pos - 2);
	cout << "| " << "Points";
	SetCursorPosition(0, hor_pos - 1);
	for (int i = 0; i <= (points_pos + 7); i++) {
		cout << "-";
	}

	while (cur) {
		SetCursorPosition(0, hor_pos);
		cout << count;
		SetCursorPosition(club_pos, hor_pos);
		cout << "| " << cur->getName();
		SetCursorPosition(series_pos, hor_pos);
		cout << "| ";
		cur->ShowSeries((num_teams * 2) - 2);
		SetCursorPosition(wins_pos, hor_pos);
		cout << "| " << cur->getWins();

		SetCursorPosition(draws_pos, hor_pos);
		cout << "| " << cur->getDraws();
		SetCursorPosition(loss_pos, hor_pos);
		cout << "| " << cur->getLosses();
		SetCursorPosition(sc_pos, hor_pos);
		cout << "| " << cur->getGoalsScored();
		SetCursorPosition(miss_pos, hor_pos);
		cout << "| " << cur->getGoalsMissed();
		SetCursorPosition(points_pos, hor_pos);
		cout << "| " << cur->getPoints();

		hor_pos += 2;
		count++;
		cur = cur->getNext();
	}
}

Club* List_Clubs::ClubInfo(int seed)
{
	Node* cur = start;
	if (cur->getSeedNum() == seed) {
		return cur->getClubInfo();
	}
	int count = 0;
	while (cur->getSeedNum() != seed) {
		cur = cur->getNext();
		count++;
	}
	return cur->getClubInfo();
}

Club* List_Clubs::ClubPos(int pos)
{
	if (pos >= 0 && pos < num_teams) {
		Node* cur = start;
		int count = 0;
		while (count != pos) {
			cur = cur->getNext();
			count++;
		}
		return cur->getClubInfo();
	}
	return nullptr;
}

List_Clubs::~List_Clubs()
{
	while (num_teams)
	{
		Popend();
	}
}
