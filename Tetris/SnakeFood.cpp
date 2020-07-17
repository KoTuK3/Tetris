#include "SnakeFood.h"

void SnakeFood::CreateFood(vector<vector<bool>>& gameField) {
	do {
		coord.x = rand() % 10;
		coord.y = rand() % 20;
	} while (gameField[coord.y][coord.x]);
	gameField[coord.y][coord.x] = true;
}

Coord SnakeFood::GetCoord() {
	return coord;
}