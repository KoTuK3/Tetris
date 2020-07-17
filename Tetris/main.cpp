#include <iostream>
#include <ctime>

#include "Tetris.h"
#include "Racing.h"
#include "Snake.h"

using namespace std;

int main() {
	srand((unsigned)time(nullptr));
	Tetris tetris;
	Racing racing;
	Snake snake;
	tetris.AddGame(&racing);
	tetris.AddGame(&snake);
	tetris.Menu();
	return 0;
}