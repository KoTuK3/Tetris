#pragma once

#include "Unit.h"

class RacingEnemy : public Unit {
private:
	bool side; // false - left, true - right
	
public:
	RacingEnemy() {}

	RacingEnemy(vector<vector<bool>>& auxiliaryField) {
		GenerateUnit();
		PutUnit(auxiliaryField, true);
	}

	void GenerateUnit() override {
		side = rand() % 2;
		y = 2;
		x = GetX(side);
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

	void Move(Moves moves) override {
		y += 1;
	}

	size_t GetY() const {
		return y;
	}

	size_t GetX(bool side) const {
		return int(side) * 3 + 3;
	}

	bool GetSide() const {
		return side;
	}
};

