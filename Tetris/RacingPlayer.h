#pragma once

#include "Unit.h"
#include "Helpers.h"

class RacingPlayer : public Unit {
private:
	bool side; // false - left, true - right
	bool lastSide;

public:
	RacingPlayer() {}

	RacingPlayer(vector<vector<bool>>& auxiliaryField) {
		GenerateUnit();
		PutUnit(auxiliaryField, true);
	}

	void GenerateUnit() override {
		side = bool(rand() % 2);
		lastSide = false;

		x = int(side) * 3 + 3;
		y = 21; // spawn line
	}

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
		x = int(side) * 3 + 3;
	}

	bool GetSide() {
		return side;
	}

	bool GetLastSide() {
		return lastSide;
	}

	void SetLastSide(bool side) {
		this->lastSide = side;
	}
};

