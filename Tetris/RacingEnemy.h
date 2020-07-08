#pragma once

#include "Unit.h"

class RacingEnemy : Unit {
private:
	bool enemySide; // false - left, true - right
	int y = 2;

public:
	void GenerateUnit() {
		enemySide = rand() % 2;
		y = 2;
	}
	//Is create should be true
	void PutUnit(vector<vector<bool>>& gameField, bool isCreate) override {
		/*
		#   #
		  #
		# # #
		  #
		*/
		gameField[y][x] =
		gameField[y][x - 1] =
		gameField[y][x + 1] =
		gameField[y - 1][x] =
		gameField[y + 1][x] =
		gameField[y - 2][x - 1] =
		gameField[y - 2][x + 1] = isCreate;
	}

	void Move() {
		y += 1;
	}

};

