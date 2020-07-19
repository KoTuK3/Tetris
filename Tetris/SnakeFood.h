#pragma once
#include <iostream>
#include <vector>

#include "Helpers.h"

using namespace std;

class SnakeFood {
private:
	Coord coord;
	Colors color;

public:
	void CreateFood(vector<vector<Colors>>& gameField);

	Coord GetCoord();
};

