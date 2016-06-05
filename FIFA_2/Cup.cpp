#include <conio.h>
#include "Cup.h"
#include "ServiceFunc.h"

Cup::Cup(List_Clubs _teams) : Tournament(_teams)
{
	Schedule();
}

void Cup::Schedule()
{
	struct pair {
		int hst;
		int gst;
		pair() : hst(0), gst(0) {};
	};

	int num_teams = teams.getNumTeams();
	int tours = 0;
	int games = 0;
	pair** schedule;

	if (PowerOfTwo(num_teams)) {
		// ���� ���������� ������ �������� �������� 2
		tours = NumberOfTours(num_teams);
		games = num_teams / 2;

		// �������� �������
		schedule = new pair*[tours];
		for (int i = 0; i < tours; i++) {
			schedule[i] = new pair[games];
			games /= 2;
		}

		// ���������� ���������� �� ��������� ������
		games = num_teams / 2;
		for (int i = 0; i < tours; i++) {
			for (int j = 0, k = (games * 2 - 1); j < games; j++, k--) {
				schedule[i][j].hst = j;
				schedule[i][j].gst = k;

				// ���������� ���������� � ������
				matches.Pushback(schedule[i][j].hst, schedule[i][j].gst, i);
			}
			games /= 2;
		}
	}
	else {
		// ���� ���������� ������ �� �������� �������� 2
		tours = NumberOfTours(num_teams) + 1;
		games = NearestPowerOfTwo(num_teams) / 2;

		// �������� �������
		schedule = new pair*[tours];
		for (int i = 0; i < tours; i++) {
			if (i == 0) {
				schedule[i] = new pair[num_teams - NearestPowerOfTwo(num_teams)];
			}
			else {
				schedule[i] = new pair[games];
				games /= 2;
			}
		}

		// ���������� ���������� �� ��������� ������
		games = NearestPowerOfTwo(num_teams) / 2;
		for (int i = 0; i < tours; i++)
		{
			if (i == 0) {
				for (int j = 0, k = ((num_teams - NearestPowerOfTwo(num_teams)) * 2) - 1; j < num_teams - NearestPowerOfTwo(num_teams); j++, k--)
				{
					schedule[i][j].hst = j;
					schedule[i][j].gst = k;

					// ���������� ���������� � ������
					matches.Pushback(schedule[i][j].hst, schedule[i][j].gst, i);
				}
			}
			else {
				for (int j = 0, k = (games * 2 - 1); j < games; j++, k--)
				{
					schedule[i][j].hst = j;
					schedule[i][j].gst = k;

					// ���������� ���������� � ������
					matches.Pushback(schedule[i][j].hst, schedule[i][j].gst, i);
				}
				games /= 2;		// � ������ ������� ��� ���������� � 2 ���� ������
			}
		}
	}

	// �������� ���������� ���������
	for (int i = 0; i < tours; i++)
	{
		delete[] schedule[i];
	}
	delete[]schedule;
}

void Cup::PlayNextStage() {
	int num_teams = teams.getNumTeams();
	int t = (PowerOfTwo(num_teams)) ? (NumberOfTours(num_teams)) : (NumberOfTours(num_teams) + 1);
	if (stage < t) {

		if (teams.getUserLeague()) {
			system("cls");
			cout << "Stage: " << stage + 1 << endl;
		}

		// ����������
		int game_pos = 2;
		int count_pos = 2;
		int host_pos = 18;

		if (PowerOfTwo(num_teams)) {
			// ���� ���������� ������ �������� �������� 2
			int games = num_teams / pow(2, stage + 1);
			for (int j = 0; j < games; j++) {

				// ��������� ���� ���������� � ���������� �����
				Match* ptrCurMatch = matches.MatchInfo(0, stage, j);

				// �����, ����������� ������� � ����
				Club* ptrHost = teams.ClubInfo(ptrCurMatch->getHost());
				Club* ptrGuest = teams.ClubInfo(ptrCurMatch->getGuest());

				// ����������� ���������� �����
				int hostScore = 0, guestScore = 0;
				int hp = 0, gp = 0;				// ��� ����� ��������, � ������ ���������� ��� �� ����� �������������

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

				// ���������� ����������� �����
				ptrCurMatch->setHostName(ptrHost->getName());
				ptrCurMatch->setGuestName(ptrGuest->getName());

				ptrCurMatch->setHostScore(hostScore);
				ptrCurMatch->setGuestScore(guestScore);

				if (hostScore == guestScore) {
					ptrCurMatch->setHostPenalty(hp);
					ptrCurMatch->setGuestPenalty(gp);
				}

				// ��������� ������� ������ ������ � ����������� �� ����, ��� ������ ������, � ��� �������
				if (hostScore > guestScore) {
					ptrHost->setSeedNum(j);
					ptrGuest->setSeedNum(-1);
				}
				else if (hostScore == guestScore) {
					if (hp > gp) {
						ptrHost->setSeedNum(j);
						ptrGuest->setSeedNum(-1);
					}
					else {
						ptrHost->setSeedNum(-1);
						ptrGuest->setSeedNum(j);
					}
				}
				else {
					ptrHost->setSeedNum(-1);
					ptrGuest->setSeedNum(j);
				}
				if (teams.getUserLeague()) {
					// ������� ���������� ������ ������ ���������������� ����
					SetCursorPosition(50, 3);
					cout << "| Press any key for the next game |";
					SetCursorPosition(0, count_pos++);
					cout << ptrHost->getName();
					SetCursorPosition(host_pos, game_pos);
					cout << ptrCurMatch->getHostScore() << " : " << ptrCurMatch->getGuestScore() << " " << ptrGuest->getName();
					if (ptrCurMatch->getHostScore() == ptrCurMatch->getGuestScore()) {
						cout << " (p " << ptrCurMatch->getHostPenalty() << " : " << ptrCurMatch->getGuestPenalty() << ")";
					}
					game_pos++;
					_getch();
				}
			}
		}
		else {
			// ���� ���������� ������ �� �������� �������� 2
			if (stage == 0) {
				// ���� ��� ������ ���
				int games = num_teams - NearestPowerOfTwo(num_teams);
				for (int j = 0; j < games; j++) {
					// ��������� ���� ���������� � ���������� �����
					Match* ptrCurMatch = matches.MatchInfo(0, stage, j);

					// �����, ����������� ������� � ����
					Club* ptrHost = teams.ClubInfo(ptrCurMatch->getHost());
					Club* ptrGuest = teams.ClubInfo(ptrCurMatch->getGuest());

					// ����������� ���������� �����
					int hostScore = 0, guestScore = 0;
					int hp = 0, gp = 0;				// ��� ����� ��������, � ������ ���������� ��� �� ����� �������������

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

					// ���������� ����������� �����
					ptrCurMatch->setHostName(ptrHost->getName());
					ptrCurMatch->setGuestName(ptrGuest->getName());

					ptrCurMatch->setHostScore(hostScore);
					ptrCurMatch->setGuestScore(guestScore);

					if (hostScore == guestScore) {
						ptrCurMatch->setHostPenalty(hp);
						ptrCurMatch->setGuestPenalty(gp);
					}

					// ��������� ������� ������ ������ � ����������� �� ����, ��� ������ ������, � ��� �������
					if (hostScore > guestScore) {
						ptrHost->setSeedNum(j);
						ptrGuest->setSeedNum(-1);
					}
					else if (hostScore == guestScore) {
						if (hp > gp) {
							ptrHost->setSeedNum(j);
							ptrGuest->setSeedNum(-1);
						}
						else {
							ptrHost->setSeedNum(-1);
							ptrGuest->setSeedNum(j);
						}
					}
					else {
						ptrHost->setSeedNum(-1);
						ptrGuest->setSeedNum(j);
					}

					if (teams.getUserLeague()) {
						// ������� ���������� ������ ������ ���������������� ����

						SetCursorPosition(50, 3);
						cout << "| Press any key for the next game |";
						SetCursorPosition(0, count_pos++);
						cout << ptrHost->getName();
						SetCursorPosition(host_pos, game_pos);
						cout << ptrCurMatch->getHostScore() << " : " << ptrCurMatch->getGuestScore() << " " << ptrGuest->getName();
						if (ptrCurMatch->getHostScore() == ptrCurMatch->getGuestScore()) {
							cout << " (p " << ptrCurMatch->getHostPenalty() << " : " << ptrCurMatch->getGuestPenalty() << ")";
						}
						game_pos++;
						_getch();
					}
				}
				// ����� ����� ������
				int num_reSeed = NearestPowerOfTwo(num_teams);
				int* mas = new int[num_reSeed];
				for (int i = games; i < num_reSeed; i++) {
					mas[i] = i;
				}
				int temp, r;
				for (int i = games; i < num_reSeed; i++) {
					r = rand() % (num_reSeed - i) + i;
					temp = mas[i];
					mas[i] = mas[r];
					mas[r] = temp;
				}
				int count = games;
				int k = 0;
				while (count != num_reSeed) {
					Club* ptr = teams.ClubPos(k);
					if (ptr->getSeedNum() != (-1) && (ptr->getSeedNum() >= games)) {
						ptr->setSeedNum(mas[count]);
						count++;
					}
					k++;
				}
				delete[]mas;
				//------------------
			}
			else {
				// ���� ��� �� ������ ���
				int games = NearestPowerOfTwo(num_teams) / pow(2, stage);
				for (int j = 0; j < games; j++) {
					// ��������� ���� ���������� � ���������� �����
					Match* ptrCurMatch = matches.MatchInfo(0, stage, j);

					// �����, ����������� ������� � ����
					Club* ptrHost = teams.ClubInfo(ptrCurMatch->getHost());
					Club* ptrGuest = teams.ClubInfo(ptrCurMatch->getGuest());

					// ����������� ���������� �����
					int hostScore = 0, guestScore = 0;
					int hp = 0, gp = 0;				// ��� ����� ��������, � ������ ���������� ��� �� ����� �������������

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

					// ���������� ����������� �����
					ptrCurMatch->setHostName(ptrHost->getName());
					ptrCurMatch->setGuestName(ptrGuest->getName());

					ptrCurMatch->setHostScore(hostScore);
					ptrCurMatch->setGuestScore(guestScore);

					if (hostScore == guestScore) {
						ptrCurMatch->setHostPenalty(hp);
						ptrCurMatch->setGuestPenalty(gp);
					}

					// ��������� ������� ������ ������ � ����������� �� ����, ��� ������ ������, � ��� �������
					if (hostScore > guestScore) {
						ptrHost->setSeedNum(j);
						ptrGuest->setSeedNum(-1);
					}
					else if (hostScore == guestScore) {
						if (hp > gp) {
							ptrHost->setSeedNum(j);
							ptrGuest->setSeedNum(-1);
						}
						else {
							ptrHost->setSeedNum(-1);
							ptrGuest->setSeedNum(j);
						}
					}
					else {
						ptrHost->setSeedNum(-1);
						ptrGuest->setSeedNum(j);
					}

					if (teams.getUserLeague()) {
						// ������� ���������� ������ ������ ���������������� ����

						SetCursorPosition(50, 3);
						cout << "| Press any key for the next game |";
						SetCursorPosition(0, count_pos++);
						cout << ptrHost->getName();
						SetCursorPosition(host_pos, game_pos);
						cout << ptrCurMatch->getHostScore() << " : " << ptrCurMatch->getGuestScore() << " " << ptrGuest->getName();
						if (ptrCurMatch->getHostScore() == ptrCurMatch->getGuestScore()) {
							cout << " (p " << ptrCurMatch->getHostPenalty() << " : " << ptrCurMatch->getGuestPenalty() << ")";
						}
						game_pos++;
						_getch();
					}
				}
			}
		}
		stage++;
	}
	else {
		is_not_ended = false;
	}
}

void Cup::UserPlay(bool user_is_host, int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp) {
	const int GAME_TIME = 90; // ����� ����

	if (user_is_host) {
		for (int i = 0; i < GAME_TIME; i += 5) {
			if ((i % 2) == 0) {
				// ���� �������-�������
				int chance = rand() % 100;
				if (chance <= hostStren) {
					int user_chance = 0;
					//SetCursorPosition(65, 10);
					//cout << "Enter any number from 0 to 9 -> ";
					//cin >> user_chance;
					//cin.ignore();


					if (user_chance < 5)
						hostScore++;
				}
			}
			else {
				// ���� �������� �������
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
				// ���� �������-�������
				int chance = rand() % 100;
				if (chance <= hostStren) {
					hostScore++;
				}
			}
			else {
				// ���� �������� �������
				int chance = rand() % 100;
				if (chance <= guestStren) {
					int user_chance = 0;
					//SetCursorPosition(40, 15);
					//cout << "Enter any number from 0 to 9 -> ";
					//cin >> user_chance;
					//cin.ignore();
					if (user_chance < 5)
						guestScore++;
				}
			}
		}
	}

	if (hostScore == guestScore) {
		// ���������� ����� ��������
		const int num_penalties = 10;
		const int chance = 50;
		for (int i = 0; i < num_penalties; i++) {
			if ((i % 2) == 0) {
				// ��������� �������
				int roulette = rand() % 100;
				if (roulette < chance) {
					hp++;
				}
			}
			else {
				// ��������� �����
				int roulette = rand() % 100;
				if (roulette < chance) {
					gp++;
				}
			}
		}
		if (hp == gp) {
			// ���� ����������� ����� �� ������� ����������, �������� ������������ �� ������� �������
			while ((hp - gp) == 0 && (gp - hp) == 0) {
				for (int i = 0; i < 2; i++) {
					if ((i % 2) == 0) {
						// ��������� �������
						int roulette = rand() % 100;
						if (roulette < chance) {
							hp++;
						}
					}
					else {
						// ��������� �����
						int roulette = rand() % 100;
						if (roulette < chance) {
							gp++;
						}
					}
				}
			}
		}
	}
}

void Cup::ComputerPlay(int hostStren, int guestStren, int& hostScore, int& guestScore, int& hp, int& gp) {
	const int GAME_TIME = 90; // ����� ����

	for (int i = 0; i < GAME_TIME; i += 5) {
		if ((i % 2) == 0) {
			// ���� �������-�������
			int chance = rand() % 100;
			if (chance <= hostStren) {
				hostScore++;
			}
		}
		else {
			// ���� �������� �������
			int chance = rand() % 100;
			if (chance <= guestStren) {
				guestScore++;
			}
		}
	}

	if (hostScore == guestScore) {
		// ���������� ����� ��������
		const int num_penalties = 10;
		const int chance = 50;
		for (int i = 0; i < num_penalties; i++) {
			if ((i % 2) == 0) {
				// ��������� �������
				int roulette = rand() % 100;
				if (roulette < chance) {
					hp++;
				}
			}
			else {
				// ��������� �����
				int roulette = rand() % 100;
				if (roulette < chance) {
					gp++;
				}
			}
		}
		if (hp == gp) {
			// ���� ����������� ����� �� ������� ����������, �������� ������������ �� ������� �������
			while ((hp - gp) == 0 && (gp - hp) == 0) {
				for (int i = 0; i < 2; i++) {
					if ((i % 2) == 0) {
						// ��������� �������
						int roulette = rand() % 100;
						if (roulette < chance) {
							hp++;
						}
					}
					else {
						// ��������� �����
						int roulette = rand() % 100;
						if (roulette < chance) {
							gp++;
						}
					}
				}
			}
		}
	}
}

void Cup::Show() {
	matches.Show();
}