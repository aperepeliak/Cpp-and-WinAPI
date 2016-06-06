#include "stdafx.h"
#include "Game_2048.h"


Game_2048::Game_2048()
{
	// �������� ����
	field_size = 4;
	field = new int*[field_size];
	for (int i = 0; i < field_size; i++) {
		field[i] = new int[field_size];
	}
	// ���������� ���� ������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			field[i][j] = 0;
		}
	}

	// �������� backup-����
	backup = new int*[field_size];
	for (int i = 0; i < field_size; i++) {
		backup[i] = new int[field_size];
	}
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			backup[i][j] = 0;
		}
	}

	maxTile = 0;
	points = 0;
	score = 0;
	winTile = 2048;
}

Game_2048::~Game_2048()
{
	for (int i = 0; i < field_size; i++) {
		delete[]field[i];
	}
	delete field;

	for (int i = 0; i < field_size; i++) {
		delete[]backup[i];
	}
	delete backup;
}

void Game_2048::StartField() {
	// �� ������ ������ ����� ���� ��������� �����
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			field[i][j] = 0;
		}
	}
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			backup[i][j] = 0;
		}
	}
	maxTile = 0;
	points = 0;
	score = 0;
	winTile = 2048;

	// ��������� ���������� ������ ���� ������ � ��������
	int i = 0;
	int j = 0;
	i = rand() % field_size;
	j = rand() % field_size;
	field[i][j] = 2;
	int k = i;
	int l = j;
	while (k == i || l == j) {
		k = rand() % field_size;
		l = rand() % field_size;
	}
	field[k][l] = 2;
}

void Game_2048::AddTile() {
	int i = 0;
	int j = 0;
	int probability = 0;

	// ��������� ����� ������ ������ ������
	do {
		i = rand() % field_size;
		j = rand() % field_size;
		probability = rand() % 10;
	} while (field[i][j]);

	// ����������� ���������� ������ � ������ 4 ��� 2
	if (probability < 2) {
		field[i][j] = 4;
	}
	else {
		field[i][j] = 2;
	}
}

void Game_2048::Show(HWND h) {
	const int TILE = 50;
	const int CELL = 65;
	const int PADDING = 27;
	for (int i = ID; i < curID; i++) {
		DestroyWindow(GetDlgItem(h, i));
	}
	curID = ID;
	TCHAR buf[5];
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j]) {
				_itow_s(field[i][j], buf, 10);
				CreateWindow(L"BUTTON", buf, WS_CHILD | WS_VISIBLE, ((i * CELL) + PADDING), ((j * CELL) + PADDING), TILE, TILE, h, HMENU(curID++), nullptr, nullptr);
			}
		}
	}
}

void Game_2048::FindMaxTile() {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] > maxTile) {
				maxTile = field[i][j];
			}
		}
	}
}

void Game_2048::MakeBackup() {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			backup[i][j] = field[i][j];
		}
	}
}

void Game_2048::Up() {
	// ��������� ���������� ���
	MakeBackup();

	// ��������� ������� �����
	points = 0;

	// ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] == 0) {
				for (int k = j + 1; k < field_size; k++) {
					if (field[i][k]) {
						field[i][j] = field[i][k];
						field[i][k] = 0;
						k = field_size;
					}
				}
			}
		}
	}

	// ��������� �������� ������ � ����������� ���������� � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size - 1; j++) {
			if (field[i][j] && field[i][j] == field[i][j + 1]) {
				field[i][j] += field[i][j + 1];
				field[i][j + 1] = 0;
				points += field[i][j];
				score += field[i][j];
			}
		}
	}

	// ����� ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] == 0) {
				for (int k = j + 1; k < field_size; k++) {
					if (field[i][k]) {
						field[i][j] = field[i][k];
						field[i][k] = 0;
						k = field_size;
					}
				}
			}
		}
	}

	// �������� ��������� ����
	GameEndCheck();
}

void Game_2048::Down() {
	// ��������� ���������� ���
	MakeBackup();

	// ��������� ������� �����
	points = 0;

	// ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = field_size - 1; j >= 0; j--) {
			if (field[i][j] == 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (field[i][k]) {
						field[i][j] = field[i][k];
						field[i][k] = 0;
						k = 0;
					}
				}
			}
		}
	}

	// ��������� �������� ������ � ����������� ���������� � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = field_size - 1; j > 0; j--) {
			if (field[i][j] && field[i][j] == field[i][j - 1]) {
				field[i][j] += field[i][j - 1];
				field[i][j - 1] = 0;
				points += field[i][j];
				score += field[i][j];
			}
		}
	}

	// ����� ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = field_size - 1; j >= 0; j--) {
			if (field[i][j] == 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (field[i][k]) {
						field[i][j] = field[i][k];
						field[i][k] = 0;
						k = 0;
					}
				}
			}
		}
	}

	// �������� ��������� ����
	GameEndCheck();
}

void Game_2048::Left() {
	// ��������� ���������� ���
	MakeBackup();

	// ��������� ������� �����
	points = 0;

	// ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[j][i] == 0) {
				for (int k = j + 1; k < field_size; k++) {
					if (field[k][i]) {
						field[j][i] = field[k][i];
						field[k][i] = 0;
						k = field_size;
					}
				}
			}
		}
	}

	// ��������� �������� ������ � ����������� ���������� � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size - 1; j++) {
			if (field[j][i] && field[j][i] == field[j + 1][i]) {
				field[j][i] += field[j + 1][i];
				field[j + 1][i] = 0;
				points += field[j][i];
				score += field[j][i];
			}
		}
	}

	// ����� ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[j][i] == 0) {
				for (int k = j + 1; k < field_size; k++) {
					if (field[k][i]) {
						field[j][i] = field[k][i];
						field[k][i] = 0;
						k = field_size;
					}
				}
			}
		}
	}

	// �������� ��������� ����
	GameEndCheck();
}

void Game_2048::Right() {
	// ��������� ���������� ���
	MakeBackup();

	// ��������� ������� �����
	points = 0;

	// ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = field_size - 1; j >= 0; j--) {
			if (field[j][i] == 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (field[k][i]) {
						field[j][i] = field[k][i];
						field[k][i] = 0;
						k = 0;
					}
				}
			}
		}
	}

	// ��������� �������� ������ � ����������� ���������� � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = field_size - 1; j > 0; j--) {
			if (field[j][i] && field[j][i] == field[j - 1][i]) {
				field[j][i] += field[j - 1][i];
				field[j - 1][i] = 0;
				points += field[j][i];
				score += field[j][i];
			}
		}
	}

	// ����� ������� ��� ������ � ��������� �����������
	for (int i = 0; i < field_size; i++) {
		for (int j = field_size - 1; j >= 0; j--) {
			if (field[j][i] == 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (field[k][i]) {
						field[j][i] = field[k][i];
						field[k][i] = 0;
						k = 0;
					}
				}
			}
		}
	}

	// �������� ��������� ����
	GameEndCheck();
}

bool Game_2048::FieldIsFull() {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] == 0)
				return false;
		}
	}
	return true;
}

bool Game_2048::MovedTiles() {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			if (field[i][j] != backup[i][j])
				return true;
		}
	}
	return false;
}

void Game_2048::Undo() {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size; j++) {
			field[i][j] = backup[i][j];
		}
	}
	score -= points;
	points = 0;
}

void Game_2048::GameEndCheck() {
	FindMaxTile();
	if (maxTile == winTile) {
		TCHAR scr_txt[50] = L"You\'ve won!!\nScore: ";
		TCHAR scr[10];
		_itow_s(score, scr, 10);
		wcscat_s(scr_txt, 50, scr);
		MessageBox(0, scr_txt, TEXT("Victory"), MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
	}
	else if (FieldIsFull()) {
		if (MovedTiles() == 0 && AreThereAnyOptions() == 0) {
			TCHAR scr_txt[50] = L"You\'ve lost\nScore: ";
			TCHAR scr[10];
			_itow_s(score, scr, 10);
			wcscat_s(scr_txt, 50, scr);
			MessageBox(0, scr_txt, TEXT("Game over"), MB_OK | MB_ICONSTOP | MB_DEFBUTTON1);
		}
	}
	else if (MovedTiles()) {
		AddTile();
	}
}

int Game_2048::getPoints() {
	return points;
}

int Game_2048::getScore() {
	return score;
}

bool Game_2048::AreThereAnyOptions() {
	for (int i = 0; i < field_size; i++) {
		for (int j = 0; j < field_size - 1; j++) {
			if (field[i][j] == field[i][j + 1])
				return true;
			if (field[j][i] == field[j + 1][i])
				return true;
		}
	}
	return false;
}