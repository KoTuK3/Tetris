#include "Tetris.h"

void Tetris::ShowChar(int x, int y, char character) {
	COORD cord;
	cord.X = x;
	cord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	cout << character;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void Tetris::ShowString(int x, int y, string str) {
	COORD cord;
	cord.X = x;
	cord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	cout << str;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

Tetris::Tetris() {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);

	system("mode con cols=150 lines=40");

	height = 20;
	width = 10;

	gameField = vector<vector<bool>>(height, vector<bool>(width, 0));
	display = vector<vector<bool>>(height, vector<bool>(width, 0));

	score = 0;
	lastScore = 1;

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = true;
			Update();
			Sleep(20);
		}
	}
}

void Tetris::Update() {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (display[i][j] != gameField[i][j]) {
				display[i][j] = gameField[i][j];
				if (display[i][j]) {
					ShowChar(j * 2, i, 219);
					ShowChar(j * 2 + 1, i, 219);
				}
				else {
					ShowChar(j * 2, i, ' ');
				}
			}
		}
		cout << endl;
	}

	if (score != lastScore) {
		lastScore = score;
		string str = to_string(score);

		while (str.length() < 6) {
			str = '0' + str;
		}

		ShowString((width + 1) * 2, 0, "Score:");
		ShowString((width + 1) * 2, 1, str);
	}
}
