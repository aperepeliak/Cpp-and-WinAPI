#pragma once

class Game_2048
{
	int field_size;				// Размер поля
	int maxTile;				// Плитка с максимальным значением
	int winTile;				// Победное значение (2048)
	int points;					// Набранные очки за ход
	int score;					// Общий счет
	int** field;				// Поле для плиток
	int** backup;				// Для сохранения предыдущего хода

	const int ID = 5000;
	int curID;
	
	void AddTile();				// Случайое добавление новой плитки на поле
	void GameEndCheck();		// Проверка окончания игры
	void FindMaxTile();			// Поиск плитки с максимальным значением
	bool FieldIsFull();			// Полностью ли заполнено поле
	void MakeBackup();			// Сохранение предыдущего хода
	bool MovedTiles();			// Было ли перемещение плиток?
	bool AreThereAnyOptions();	// Все поле заполнено и не осталось вариантов перемещения

public:
	Game_2048();
	~Game_2048();

	int getPoints();
	int getScore();

	void StartField();			// Первоначальное размещение двух плиток

								// Обработка нажатий клавиш
	void Up();
	void Down();
	void Left();
	void Right();

	void Undo();				// Отмена хода
	void Show(HWND h);			// Отображение плиток на поле

};

