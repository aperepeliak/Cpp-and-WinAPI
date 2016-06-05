#pragma once
#include "Tournament.h"

using namespace std;

class FIFA
{
	int num_leagues;							// Количество лиг
	int difficulty;								// Уровень сложности
	List_Clubs* leagues;						// Лиги, загружаемые в игру
	Tournament** game;							// Все проводимые турниры

	void LoadLeagues();							// Загрузка всех лиг в программу
	void Chooseleague();						// Меняем поле userLeague выбранной лиги на true 
	void ChooseClub(int i);						// Меняем поле userClub выбранной команды на true
	void ChooseDifficulty();					// Определяем уровень сложности игры для пользователя
	int FindChosenLeague();						// Для выбора клуба
	
	void StartMenu();							// Стартовое меню для выбора ползователем лиги и команды	
	void CreateTournaments();					// После загрузки всех лиг, создаем турниры

	void BrowseMenu(int option = 0);			// Для просмотра таблиц других лиг между турами

public:
	FIFA();
	void Play();								// Единый такт для всех турниров (в чемпионате - это тур, в кубке - этап 1/n финала)
	~FIFA();
};

