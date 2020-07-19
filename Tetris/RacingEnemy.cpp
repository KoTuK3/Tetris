#include "RacingEnemy.h"

RacingEnemy::RacingEnemy(vector<vector<Colors>>& auxiliaryField) {
	GenerateUnit();
	PutUnit(auxiliaryField, true);
}

void RacingEnemy::GenerateUnit() {
	color = Colors::RED;
	side = rand() % 2;
	y = 2;
	x = GetX(side);
}

void RacingEnemy::PutUnit(vector<vector<Colors>>& gameField, bool isCreate) {
	Colors localColor = Colors::NONE;
	if (isCreate) {
		localColor = color;
	}
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
		gameField[y - 2][x + 1] = localColor;
}

void RacingEnemy::Move(Moves moves) {
	y += 1;
}

size_t RacingEnemy::GetY() const {
	return y;
}

size_t RacingEnemy::GetX(bool side) const {
	return int(side) * 3 + 3;
}

bool RacingEnemy::GetSide() const {
	return side;
}
