#include "RacingPlayer.h"

RacingPlayer::RacingPlayer(vector<vector<Colors>>& auxiliaryField) {
	minDelay = 40;
	maxDelay = 80;

	GenerateUnit();
	PutUnit(auxiliaryField, true);
}

void RacingPlayer::GenerateUnit() {
	color = Colors::BLUE;
	side = bool(rand() % 2);
	lastSide = false;

	x = GetX(side);
	y = 21; // spawn line
}

void RacingPlayer::PutUnit(vector<vector<Colors>>& gameField, bool isCreate) {
	Colors localColor = Colors::NONE;
	if (isCreate) {
		localColor = color;
	}
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
		gameField[y + 2][x + 1] = localColor;
}

void RacingPlayer::Move(Moves moves) {
	lastSide = side;
	switch (moves) {
	case Moves::LEFT:
		side = false; break;
	case Moves::RIGHT:
		side = true; break;
	case Moves::ENTER: case Moves::UP:
		if (minDelay != delay)
			SetDelay(minDelay); break;
	case Moves::NONE:
		if (maxDelay != delay)
			SetDelay(maxDelay); break;
	}
	// update x after move
	x = GetX(side);
}

bool RacingPlayer::GetSide() const {
	return side;
}

bool RacingPlayer::GetLastSide() const {
	return lastSide;
}

void RacingPlayer::SetLastSide(bool side) {
	this->lastSide = side;
}

size_t RacingPlayer::GetDelay() const {
	return delay;
}

size_t RacingPlayer::GetX(bool side) const {
	return int(side) * 3 + 3;
}

void RacingPlayer::SetDelay(size_t delay) {
	this->delay = delay;
}
