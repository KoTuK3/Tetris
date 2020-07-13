#pragma once
#include <iostream>
#include <vector>

#include "Helpers.h"

using namespace std;

class SnakeFood {
private:
	Coord coord;

public:
	void CreateFood(vector<vector<bool>>& gameField) {
		do {
			coord.x = rand() % 10;
			coord.y = rand() % 20;
		} while (gameField[coord.y][coord.x]);
		gameField[coord.y][coord.x] = true;
	}

	Coord GetCoord() {
		return coord;
	}
};

