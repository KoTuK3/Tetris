#include <iostream>
#include <ctime>

#include "Tetris.h"
#include "Racing.h"
#include "Snake.h"
#include "TetrisGame.h"

using namespace std;

int main() {
	srand((unsigned)time(nullptr));
	Tetris tetris;
	Racing racing;
	Snake snake;
	TetrisGame tetrisGame;
	tetris.AddGame(&racing);
	tetris.AddGame(&snake);
	tetris.AddGame(&tetrisGame);

	//tetris.Play(2);
	tetris.Menu();
	return 0;
}