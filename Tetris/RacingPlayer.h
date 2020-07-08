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

	void GenerateUnit() override {}

	void PutUnit(vector<vector<bool>>& gameField, bool isCreate) override {
		/*
		  #
		# # #
		  #
		#   #
		*/
		gameField[y][x] =
		gameField[y][x - 1] =
		gameField[y][x + 1] =
		gameField[y - 1][x] =
		gameField[y + 1][x] =
		gameField[y + 2][x - 1] =
		gameField[y + 2][x + 1] = isCreate;
	}

	void Move(Moves moves) override {
		lastSide = side;
		switch (moves) {
			case Moves::LEFT:
				side = false; break;
			case Moves::RIGHT:
				side = true; break;
		}
		// update x after move
		x = int(side) * 3;
	}
};

