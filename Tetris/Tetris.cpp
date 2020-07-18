#include "Tetris.h"
#include "Racing.h"
#include "Snake.h"
#include "Game.h"

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
		case 32: case 13:
			return Moves::ENTER;
			break;
		}
	}
	return Moves::NONE;
}

void Tetris::Play(int index) {
	if (index >= 0 && index < games.size()) {
		bool isLose = true;
		do {
			isLose = games[index]->Play(gameField, score, Move());
			//games[index]->Preview(gameField);
			Update();
			Sleep(games[index]->GetDelay());
		} while (isLose);
		Reset(index);
	}
}

void Tetris::Preview(int index) {
	if (index >= 0 && index < games.size()) {
		games[index]->Preview(gameField);
		Update();
		Sleep(games[index]->GetDelay());
	}
}

void Tetris::Reset(int index) {
	ClearDisplay();
	games[index]->Reset();
	score = 0;
	lastScore = 1;
}

void Tetris::Menu() {
	int index = 0;
	Moves move;
	do {
		Preview(index);

		move = Move();
		switch (move) {
			case Moves::RIGHT:
				Reset(index);
				index += 1;
				break;
			case Moves::LEFT:
				Reset(index);
				index -= 1;
				break;
			case Moves::ENTER:
				Reset(index);
				Animation();
				Play(index);
				Reset(index);
				Animation();
				break;
			case Moves::NONE:
				break;
		}
		if (index == -1)
			index = games.size() - 1;
		else if (index == games.size())
			index = 0;

	} while (true);


}

void Tetris::ClearDisplay() {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = false;
			ShowChar(j * 2, i, 176);
			ShowChar(j * 2 + 1, i, 176);
		}
	}
	Update();
}

void Tetris::Animation() {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = true;
			Update();
			Sleep(10);
		}
	}
}

Tetris::Tetris() {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);

	system("mode con cols=150 lines=50");

	height = 20;
	width = 10;

	gameField = vector<vector<bool>>(height, vector<bool>(width, 0));
	display = vector<vector<bool>>(height, vector<bool>(width, 0));

	score = 0;
	lastScore = 1;
	
	// Start preview
	ClearDisplay();

	Animation();
}

void Tetris::Update() {
	bool isUpdated = false;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (display[i][j] != gameField[i][j]) {
				isUpdated = true;
				display[i][j] = gameField[i][j];
				if (display[i][j]) {
					ShowChar(j * 2, i, 219);
					ShowChar(j * 2 + 1, i, 219);
				}
				else {
					ShowChar(j * 2, i, 176);
					ShowChar(j * 2 + 1, i, 176);
					//ShowString(j * 2, i, "  ");
				}
			}
		}
		if (isUpdated)
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

void Tetris::AddGame(Game* game) {
	games.push_back(game);
}
