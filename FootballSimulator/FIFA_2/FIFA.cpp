#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "ServiceFunc.h"
#include "FIFA.h"
#include "Champ.h"
#include "Cup.h"

using namespace std;

void ClearLine() {
	cout << "                                              ";
}

FIFA::FIFA()
{
	num_leagues = 0;
	difficulty = 0;
	leagues = nullptr;
	game = nullptr;
}

// Реализация стартового меню
void FIFA::StartMenu()
{
	LoadLeagues();
	Chooseleague();
	int i = -1;
	i = FindChosenLeague();
	if (i != (-1))
		ChooseClub(i);
	else
		cout << "Could not find your league" << endl;
	ChooseDifficulty();
}

void FIFA::LoadLeagues()
{
	string filename = "Leagues.txt";
	string* leagues_names;
	fstream fs;

	// Считывание количества лиг
	fs.open(filename, ios::in);
	if (fs.is_open()) {
		fs >> num_leagues;
		fs.close();
	}

	// Создание динамического массива лиг
	leagues = new List_Clubs[num_leagues];

	// Считывание названий лиг во временный контейнер
	leagues_names = new string[num_leagues];

	fs.open(filename, ios::in);
	if (fs.is_open()) {
		fs.seekg(3, ios::beg);
		for (int i = 0; i < num_leagues; i++) {
			getline(fs, leagues_names[i]);
		}
		fs.close();
	}

	for (int i = 0; i < num_leagues; i++) {
		leagues[i].setLeagueName(leagues_names[i]);
	}

	// Считывание составов всех лиг
	for (int i = 0; i < num_leagues; i++) {
		int num_teams_tmp = 0;
		string leagueFileName = leagues[i].getLeagueName();
		leagueFileName += ".txt";

		// Считывание количества команд
		fs.open(leagueFileName, ios::in);
		if (fs.is_open()) {
			fs >> num_teams_tmp;
			fs.close();
		}

		// Считывание команд во временный контейнер
		string* teams_tmp = new string[num_teams_tmp];
		fs.open(leagueFileName, ios::in);
		if (fs.is_open()) {
			fs.seekg(4, ios::beg);
			for (int j = 0; j < num_teams_tmp; j++) {
				getline(fs, teams_tmp[j]);
			}
			fs.close();
		}

		// Считывание силы команд во временный массив
		int* mas_stren = new int[num_teams_tmp];
		for (int j = 0; j < num_teams_tmp; j++) {
			char tmp1 = teams_tmp[j][0];
			char tmp2 = teams_tmp[j][1];
			char buf[] = { tmp1, tmp2, '\0' };
			mas_stren[j] = atoi(buf);
		}

		// Очистка названий команд от показателя силы
		for (int j = 0; j < num_teams_tmp; j++) {
			teams_tmp[j].erase(teams_tmp[j].begin(), teams_tmp[j].begin() + 3);
		}

		// Сохранение данных в список
		for (int j = 0; j < num_teams_tmp; j++) {
			leagues[i].Pushback(teams_tmp[j], mas_stren[j]);
		}

		delete[]mas_stren;
		delete[]teams_tmp;
	}
	delete[]leagues_names;
}

void FIFA::Chooseleague()
{
	int n = num_leagues;
	int count = 0;
	bool enter_pressed = false;
	int input;

	cout << "Welcome to FIFA Console." << "\nChoose league you want to play:" << endl;
	cout << "(Press LEFT, RIGHT buttons to browse leagues, and ENTER to choose)" << endl;

	cout << "< " << leagues[count].getLeagueName() << " >";

	while (!enter_pressed)
	{
		input = _getch();
		switch (input) {
		case 77:	// Если нажата клавиша "вправо"
			(count < n - 1) ? (count++) : (count = 0);
			SetCursorPosition(0, 3);
			ClearLine();
			SetCursorPosition(0, 3);
			cout << "< " << leagues[count].getLeagueName() << " >";
			break;

		case 75:	// Если нажата клавиша "влево"
			(count == 0) ? (count = n - 1) : (count--);
			SetCursorPosition(0, 3);
			ClearLine();
			SetCursorPosition(0, 3);
			cout << "< " << leagues[count].getLeagueName() << " >";
			break;

		case 13:	// Если нажата клавиша "enter"
			enter_pressed = true;
			leagues[count].setUserLeague(true);
			break;
		}
	}
}

void FIFA::ChooseClub(int i)
{
	int count = 0;
	bool enter_pressed = false;
	int input;

	cout << "\nChoose team you want to manage: " << endl;

	Club* ptr = leagues[i].ClubPos(count);
	cout << "< " << ptr->getName() << " >";

	while (!enter_pressed) {
		input = _getch();
		switch (input) {
		case 77:	// Если нажата клавиша "вправо"
			(count < (leagues[i].getNumTeams() - 1)) ? (count++) : (count = 0);
			SetCursorPosition(0, 5);
			ClearLine();
			SetCursorPosition(0, 5);
			ptr = leagues[i].ClubPos(count);
			cout << "< " << ptr->getName() << " >";
			break;
		case 75:
			(count == 0) ? (count = (leagues[i].getNumTeams() - 1)) : (count--);
			SetCursorPosition(0, 5);
			ClearLine();
			SetCursorPosition(0, 5);
			ptr = leagues[i].ClubPos(count);
			cout << "< " << ptr->getName() << " >";
			break;
		case 13:
			enter_pressed = true;
			ptr->setUserClub(true);
			break;
		}
	}
}

void FIFA::ChooseDifficulty()
{
	const int NUM_MODES = 3;	// Количество уровней сложности
	difficulty = 0;
	bool enter_pressed = false;
	int input;
	cout << "\nChoose difficulty mode: " << endl;
	string modes[NUM_MODES] = { "Amateur", "Professional", "World Class" };
	string choice = modes[difficulty];
	cout << "< " << modes[difficulty] << " >";
	while (!enter_pressed) {
		input = _getch();
		switch (input) {
		case 77:	// Если нажата клавиша "вправо"
			(difficulty < NUM_MODES - 1) ? (difficulty++) : (difficulty = 0);
			SetCursorPosition(0, 7);
			ClearLine();
			SetCursorPosition(0, 7);
			cout << "< " << modes[difficulty] << " >";
			break;
		case 75:	// Если нажата клавиша "влево"
			(difficulty == 0) ? (difficulty = NUM_MODES - 1) : (difficulty--);
			SetCursorPosition(0, 7);
			ClearLine();
			SetCursorPosition(0, 7);
			cout << "< " << modes[difficulty] << " >";
			break;
		case 13:	// Если нажата клавиша "enter"
			enter_pressed = true;
			break;
		}
	}
}

int FIFA::FindChosenLeague()
{
	for (int i = 0; i < num_leagues; i++) {
		if (leagues[i].getUserLeague()) {
			return i;
		}
	}
	return -1;
}
// Окончание реализации стартового меню

void FIFA::CreateTournaments()
{
	//Сперва проходят чемпионаты
	game = new Tournament*[num_leagues * 2];
	for (int i = 0; i < num_leagues; i++) {
		game[i] = new Champ(leagues[i]);
	}
	// Затем кубки национальных лиг
	for (int i = num_leagues, k = 0; i < num_leagues * 2; i++, k++) {
		game[i] = new Cup(leagues[k]);
	}
}

void FIFA::Play()
{
	StartMenu();
	CreateTournaments();
	bool f = true;
	int user_finished = 0;
	while (f) {
		f = false;
		for (int i = 0; i < num_leagues; i++) {
			if (game[i]->TournamentNotEnded()) {
				f = true;
				if (game[i]->UserLeague()) {
					user_finished = i;
					game[i]->PlayNextStage();
					game[i]->Show();
					cout << "\n\nPress any key for the next tour.";
					_getch();
				}
				else {
					game[i]->PlayNextStage();
				}
			}
		}
		if (game[user_finished]->TournamentNotEnded()) {
			cout << "\nTo view other champs press 'y'" << endl;
			char y = 0;
			y = _getch();
			if (y == 'y') {
				BrowseMenu();
			}
		}
	}

	// Все чемпионаты завершились, переход к розыгрышу кубков
	system("cls");
	cout << "All the national championships have ended!" << endl;
	cout << "Press 'y' if you want to view final tables or any other key to start national cups!" << endl;
	char y = 0;
	y = _getch();
	if (y == 'y') {
		BrowseMenu();
	}
	system("cls");
	cout << "National CUPS!!!" << endl;
	cout << "\n\nPress any key..";
	_getch();

	f = true;
	user_finished = 0;

	while (f) {
		f = false;
		for (int i = num_leagues; i < num_leagues * 2; i++) {
			if (game[i]->TournamentNotEnded()) {
				f = true;
				if (game[i]->UserLeague()) {
					user_finished = i;
					game[i]->PlayNextStage();
					game[i]->Show();
					SetCursorPosition(10, 50);
					cout << "\n\nPress any key for the next tour.";
					_getch();
				}
				else {
					game[i]->PlayNextStage();
				}
			}
		}
		if (game[user_finished]->TournamentNotEnded()) {
			cout << "\nTo view other champs press 'y'" << endl;
			char y = 0;
			y = _getch();
			if (y == 'y') {
				BrowseMenu(1);
			}
		}
	}

	system("cls");
	cout << "All the national cups have ended!" << endl;
	cout << "Press 'y' if you want to view final tables.." << endl;
	y = 0;
	y = _getch();
	if (y == 'y') {
		BrowseMenu(1);
	}
	system("cls");
	cout << "End of the season!!!" << endl;
	cout << "\n\nPress any key.." << endl;
	SetConsoleColorTextBackground(clWhite, clWhite);
	cout << endl;
}

void FIFA::BrowseMenu(int option) {
	int init_count = 0;
	int init_n = num_leagues;
	if (option) {
		init_count = num_leagues;
		init_n = 2 * num_leagues;
	}
	system("cls");
	int n = init_n;
	bool enter_pressed = false;
	int count = init_count;
	int input;

	cout << "Choose league you want to view: ";
	cout << "< " << game[count]->getLeagueName() << " >" << endl;

	cout << "\n| Press LEFT, RIGHT buttons to view other leagues |" << endl;
	cout << "\n| Press ENTER to proceed to the next stage |";

	game[count]->Show();

	while (!enter_pressed)
	{
		input = _getch();
		switch (input) {
		case 77:	// Если нажата клавиша "вправо"
			(count < n - 1) ? (count++) : (count = init_count);
			system("cls");
			cout << "Choose league you want to view: ";
			cout << "< " << game[count]->getLeagueName() << " >" << endl;
			cout << "\n| Press LEFT, RIGHT buttons to view other leagues |" << endl;
			cout << "\n| Press ENTER to proceed to the next stage |";
			game[count]->Show();
			break;

		case 75:	// Если нажата клавиша "влево"
			(count == init_count) ? (count = n - 1) : (count--);
			system("cls");
			cout << "Choose league you want to view: ";
			cout << "< " << game[count]->getLeagueName() << " >" << endl;
			cout << "\n| Press LEFT, RIGHT buttons to view other leagues |" << endl;
			cout << "\n| Press ENTER to proceed to the next stage |";
			game[count]->Show();
			break;

		case 13:	// Если нажата клавиша "enter"
			enter_pressed = true;
			break;
		}
	}
}

FIFA::~FIFA()
{
	if (num_leagues) {
		delete[]leagues;

		for (int i = 0; i < num_leagues * 2; i++) {
			delete[]game[i];
		}
		delete[] game;
	}
}
