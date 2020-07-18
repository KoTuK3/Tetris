#include <iostream>
#include <ctime>

#include "SFML/Graphics.hpp"

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
	//tetris.Menu();
	tetris.MenuSFML();
	return 0;
}