#include "SnakeFood.h"

void SnakeFood::CreateFood(vector<vector<Colors>>& gameField) {
	color = Colors::GREEN;
	do {
		coord.x = rand() % 10;
		coord.y = rand() % 20;
	} while (gameField[coord.y][coord.x] != Colors::NONE);
	gameField[coord.y][coord.x] = color;
}

Coord SnakeFood::GetCoord() {
	return coord;
}