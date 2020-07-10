#include "Tetris.h"
#include "Racing.h"

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

bool Tetris::IsUpdate() {
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (display[i][j] != gameField[i][j])
				return true;

	if (score != lastScore)
		return true;

	return false;
}

Moves Tetris::Move() {
	if (_kbhit()) {
		switch (_getch()) {
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			return Moves::UP;
			break;
			//a = 97; A = 65; Left arrow = 75
		case 97: case 65: case 75:
			return Moves::LEFT;
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			return Moves::DOWN;
			break;
			//d = 100; D = 68; Right arrow = 77
		case 100: case 68: case 77:
			return Moves::RIGHT;
			break;
			//Enter
		case 13:
			return Moves::ENTER;
			break;
		}
	}
}

void Tetris::Play() {


	Racing rc;
	
	//rc.Play(gameField, score);
	bool isLose;
	do {
		isLose = rc.Play(gameField, score, Move());
		Update();

	} while (isLose);
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
	
	/*for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = true;
			Update();
			Sleep(10);
		}
	}*/	
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
					ShowString(j * 2, i, "  ");
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
