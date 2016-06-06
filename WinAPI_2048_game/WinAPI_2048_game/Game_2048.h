#pragma once

class Game_2048
{
	int field_size;				// ������ ����
	int maxTile;				// ������ � ������������ ���������
	int winTile;				// �������� �������� (2048)
	int points;					// ��������� ���� �� ���
	int score;					// ����� ����
	int** field;				// ���� ��� ������
	int** backup;				// ��� ���������� ����������� ����

	const int ID = 5000;
	int curID;
	
	void AddTile();				// �������� ���������� ����� ������ �� ����
	void GameEndCheck();		// �������� ��������� ����
	void FindMaxTile();			// ����� ������ � ������������ ���������
	bool FieldIsFull();			// ��������� �� ��������� ����
	void MakeBackup();			// ���������� ����������� ����
	bool MovedTiles();			// ���� �� ����������� ������?
	bool AreThereAnyOptions();	// ��� ���� ��������� � �� �������� ��������� �����������

public:
	Game_2048();
	~Game_2048();

	int getPoints();
	int getScore();

	void StartField();			// �������������� ���������� ���� ������

								// ��������� ������� ������
	void Up();
	void Down();
	void Left();
	void Right();

	void Undo();				// ������ ����
	void Show(HWND h);			// ����������� ������ �� ����

};

