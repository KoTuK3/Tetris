#pragma once
#include <iostream>
#include <vector>

#include "Helpers.h"

using namespace std;

class SnakeFood {
private:
	Coord coord;

public:
	void CreateFood(vector<vector<bool>>& gameField);

	Coord GetCoord();
};

