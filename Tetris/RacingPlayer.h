#pragma once

#include "Unit.h"
#include "Helpers.h"

class RacingPlayer : public Unit {
private:
	bool side; // false - left, true - right
	bool lastSide;

	size_t delay; // For speed
	size_t minDelay;
	size_t maxDelay;

public:
	RacingPlayer() {}

	RacingPlayer(vector<vector<bool>>& auxiliaryField) {
		minDelay = 40;
		maxDelay = 80;

		GenerateUnit();
		PutUnit(auxiliaryField, true);
	}

	void GenerateUnit() override {
		side = bool(rand() % 2);
		lastSide = false;

		x = GetX(side);
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
			case Moves::ENTER:
				if (minDelay != maxDelay)
					SetDelay(minDelay); break;
			case Moves::NONE:
				if (maxDelay != minDelay)
					SetDelay(maxDelay); break;
		}
		// update x after move
		x = GetX(side);
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

	size_t GetDelay() {
		return delay;
	}

	void SetDelay(size_t delay) {
		this->delay = delay;
	}

	size_t GetX(bool side) {
		return int(side) * 3 + 3;
	}
};

