#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Champ.h"


Champ::Champ(List_Clubs _teams) : Tournament(_teams)
{
	Schedule();
}

void Champ::Schedule()
{
	struct pair {
		int hst;
		int gst;
		pair() : hst(0), gst(0) {};
	};

	int num_teams = teams.getNumTeams();
	int tours = num_teams - 1;
	int games = num_teams / 2;

	// Создание временных хранилищ под сгенерированные пары
	pair** schedule_1st_round = new pair*[tours];
	for (int i = 0; i < tours; i++) {
		schedule_1st_round[i] = new pair[games];
	}
	pair** schedule_2nd_round = new pair*[tours];
	for (int i = 0; i < tours; i++) {
		schedule_2nd_round[i] = new pair[games];
	}

	// Расписание первого круга чемпионата
	for (int i = 0; i < tours; i++) {
		for (int j = 0; j < games; j++) {
			if (j) {
				if ((i % 2) == 0) {
					schedule_1st_round[i][j].hst = (j - i <= 0) ? (j - i + tours) : (j - i);
					schedule_1st_round[i][j].gst = (tours - j - i <= 0) ? (2 * tours - j - i) : (tours - j - i);
				}
				else {
					schedule_1st_round[i][j].gst = (j - i <= 0) ? (j - i + tours) : (j - i);
					schedule_1st_round[i][j].hst = (tours - j - i <= 0) ? (2 * tours - j - i) : (tours - j - i);
				}
			}
			else {
				if ((i % 2) == 0) {
					schedule_1st_round[i][j].hst = j;
					schedule_1st_round[i][j].gst = tours - i;
				}
				else {
					schedule_1st_round[i][j].gst = j;
					schedule_1st_round[i][j].hst = tours - i;
				}
			}
			matches.Pushback(schedule_1st_round[i][j].hst, schedule_1st_round[i][j].gst, i, 0);
		}
	}

	// Расписание второг круга чемпионата
	for (int i = 0; i < tours; i++) {
		for (int j = 0; j < games; j++) {
			schedule_2nd_round[i][j].hst = schedule_1st_round[i][j].gst;
			schedule_2nd_round[i][j].gst = schedule_1st_round[i][j].hst;
			matches.Pushback(schedule_2nd_round[i][j].hst, schedule_2nd_round[i][j].gst, i, 1);
		}
	}

	// Удаление временных хранилищ
	for (int i = 0; i < games; i++) {
		delete[]schedule_1st_round[i];
	}
	delete[]schedule_1st_round;

	for (int i = 0; i < games; i++) {
		delete[]schedule_2nd_round[i];
	}
	delete[]schedule_2nd_round;
}

void Champ::PlayNextStage() {
	if (stage < (teams.getNumTeams() * 2) - 2) {
		int r = (stage < (teams.getNumTeams() - 1)) ? 0 : 1; // Определяем какой сейчас круг чемпионата
		int t = (stage < (teams.getNumTeams() - 1)) ? stage : (stage - (teams.getNumTeams() - 1));
		int games = teams.getNumTeams() / 2;

		if (teams.getUserLeague()) {
			system("cls");
			cout << "Round: " << r + 1 << "  |  ";
			cout << "Tour: " << t + 1 << endl;
		}

		// Координаты
		int game_pos = 2;
		int count_pos = 2;
		int host_pos = 18;

		for (int j = 0; j < games; j++) {

			// Получение всей информации о проходящем матче
			Match* ptrCurMatch = matches.MatchInfo(r, t, j);

			// Клубы, принимающие участие в игре
			Club* ptrHost = teams.ClubInfo(ptrCurMatch->getHost());
			Club* ptrGuest = teams.ClubInfo(ptrCurMatch->getGuest());

			// Определение результата матча
			int hostScore = 0, guestScore = 0;
			int hp = 0, gp = 0;				// Для серии пенальти, в случае чемпионата они не будут задействованы

			if (ptrHost->getUserClub() || ptrGuest->getUserClub()) {
				if (ptrHost->getUserClub()) {
					UserPlay(true, ptrHost->getStrength(), ptrGuest->getStrength(), hostScore, guestScore, hp, gp);
				}
				else {
					UserPlay(false, ptrHost->getStrength(), ptrGuest->getStrength(), hostScore, guestScore, hp, gp);
				}
			}
			else {
				ComputerPlay(ptrHost->getStrength(), ptrGuest->getStrength(), hostScore, guestScore, hp, gp);
			}

			// Сохранение результатов матча
			ptrCurMatch->setHostScore(hostScore);
			ptrCurMatch->setGuestScore(guestScore);

			ptrHost->AddToSeries(hostScore, guestScore);
			ptrGuest->AddToSeries(guestScore, hostScore);

			ptrHost->setGoalsScored(ptrHost->getGoalsScored() + hostScore);
			ptrHost->setGoalsMissed(ptrHost->getGoalsMissed() + guestScore);

			ptrGuest->setGoalsScored(ptrGuest->getGoalsScored() + guestScore);
			ptrGuest->setGoalsMissed(ptrGuest->getGoalsMissed() + hostScore);

			if (hostScore > guestScore) {
				int hostPoints = ptrHost->getPoints();
				int hostWins = ptrHost->getWins();
				int guestLosses = ptrGuest->getLosses();
				hostPoints += 3;
				hostWins++;
				guestLosses++;
				ptrHost->setPoints(hostPoints);
				ptrHost->setWins(hostWins);
				ptrGuest->setLosses(guestLosses);
			}
			else if (hostScore < guestScore) {
				int guestPoints = ptrGuest->getPoints();
				int guestWins = ptrGuest->getWins();
				int hostLosses = ptrHost->getLosses();
				guestPoints += 3;
				guestWins++;
				hostLosses++;
				ptrGuest->setPoints(guestPoints);
				ptrHost->setLosses(hostLosses);
				ptrGuest->setWins(guestWins);
			}
			else {
				int hostPoints = ptrHost->getPoints();
				int guestPoints = ptrGuest->getPoints();
				int hostDraws = ptrHost->getDraws();
				int guestDraws = ptrGuest->getDraws();
				hostPoints++;
				guestPoints++;
				hostDraws++;
				guestDraws++;
				ptrHost->setPoints(hostPoints);
				ptrGuest->setPoints(guestPoints);
				ptrHost->setDraws(hostDraws);
				ptrGuest->setDraws(guestDraws);
			}

			if (teams.getUserLeague()) {
				// Выводим результаты матчей только пользовательской лиги
				SetCursorPosition(45, 3);
				cout << "| Press any key for the next game |";
				SetCursorPosition(0, count_pos++);
				cout << ptrHost->getName();
				SetCursorPosition(host_pos, game_pos);
				cout << ptrCurMatch->getHostScore() << " : " << ptrCurMatch->getGuestScore() << " " << ptrGuest->getName() << endl;
				game_pos++;
				_getch();
			}
		}
		stage++;
	}
	else {
		is_not_ended = false;
	}
}

void Champ::UserPlay(bool user_is_host, int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp) {
	
	// Пользовательский геймплей пока не реализован


	const int GAME_TIME = 90; // время игры
	const int ADVANTAGE = 5;  // поддержка 12-го игрока
	if (user_is_host) {
		for (int i = 0; i < GAME_TIME; i += 5) {
			if ((i % 2) == 0) {
				// Шанс команды-хозяйки
				int chance = rand() % 100;
				if (chance <= (hostStren + ADVANTAGE)) {
					hostScore++;
				}
			}
			else {
				// Шанс гостевой команды
				int chance = rand() % 100;
				if (chance <= guestStren) {
					guestScore++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < GAME_TIME; i += 5) {
			if ((i % 2) == 0) {
				// Шанс команды-хозяйки
				int chance = rand() % 100;
				if (chance <= (hostStren + ADVANTAGE)) {
					hostScore++;
				}
			}
			else {
				// Шанс гостевой команды
				int chance = rand() % 100;
				if (chance <= guestStren) {
					guestScore++;
				}
			}
		}
	}
}

void Champ::ComputerPlay(int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp) {
	const int GAME_TIME = 90; // время игры
	const int ADVANTAGE = 5;  // поддержка 12-го игрока

	for (int i = 0; i < GAME_TIME; i += 5) {
		if ((i % 2) == 0) {
			// Шанс команды-хозяйки
			int chance = rand() % 100;
			if (chance <= (hostStren + ADVANTAGE)) {
				hostScore++;
			}
		}
		else {
			// Шанс гостевой команды
			int chance = rand() % 100;
			if (chance <= guestStren) {
				guestScore++;
			}
		}
	}
}

void Champ::Show() {
	teams.ShowTempoTable();
}


