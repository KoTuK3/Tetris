#pragma once

#include "Unit.h"
#include "Helpers.h"

class RacingPlayer : Unit {
private:
	bool side; // false - left, true - right
	bool lastSide;

	

public:
	RacingPlayer() {
		side = bool(rand() % 2);
		lastSide = false;

		x = int(side) * 3;
		y = 21; // spawn line
	}

	void GenerateUnit() {

	}

	void PutUnit(vector<vector<bool>>& gameField, bool isCreate) override {
		gameField[y][x] =
			gameField[y][x - 1] =
			gameField[y][x + 1] =
			gameField[y - 1][x] =
			gameField[y + 1][x] =
			gameField[y + 2][x - 1] =
			gameField[y + 2][x + 1] = isCreate;
	}
};

