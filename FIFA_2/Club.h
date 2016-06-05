#pragma once
#include <vector>
#include "Match.h"

using namespace std;

class Club
{
protected:
	bool userClub;						// Если команда управляется пользователем - true
	vector<Match> series;				// Для отслеживания серии команды и составления таблицы-градусника 

	string name;						// Название клуба
	int seed_num;						// Номер посева
	int points;							// Количество набранных очков
	int goals_scored;					// Количество забитых голов
	int goals_missed;					// Количество пропущенных голов
	int wins;							// Количество побед
	int draws;							// Количество ничьих
	int losses;							// Количество поражений

	int strength;						// Cила команды

public:
	Club(string n, int stren);
	Club(string n, int stren, bool userCl);
	void setSeedNum(int num) { seed_num = num; }
	void setPoints(int p) { points = p; }
	void setGoalsScored(int goals_s) { goals_scored = goals_s; }
	void setGoalsMissed(int goals_m) { goals_missed = goals_m; }
	void setWins(int w) { wins = w; }
	void setDraws(int d) { draws = d; }
	void setLosses(int l) { losses = l; }
	void setUserClub(bool u) { userClub = u; }
	void setStrength(int s) { strength = s; }

	string getName() { return name; }
	int getSeedNum() { return seed_num; }
	int getPoints() { return points; }
	int getGoalsScored() { return goals_scored; }
	int getGoalsMissed() { return goals_missed; }
	int getWins() { return wins; }
	int getDraws() { return draws; }
	int getLosses() { return losses; }
	bool getUserClub() { return userClub; }
	int getStrength() { return strength; }

	void AddToSeries(int h_sc, int g_sc);
	vector<Match> GetSeries() { return series; }
	void ShowSeries(int num_games);
};

