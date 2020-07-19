#include "TetrisGame.h"

TetrisGame::TetrisGame() {
	height = 24;
	width = 10;

	minDelay = 50;
	maxDelay = 150;

	figures.push_back({ 1,3,5,7 });	 // I
	figures.push_back({ 2,4,5,7 });	 // S
	figures.push_back({ 3,5,4,6 });	 // Z
	figures.push_back({ 3,5,4,7 });	 // T
	figures.push_back({ 2,3,5,7 });	 // L
	figures.push_back({ 3,5,7,6 });	 // J
	figures.push_back({ 2,3,4,5 });	 // O

	Reset();
}

void TetrisGame::Reset() {
	auxiliaryField = vector<vector<Colors>>(height, vector<Colors>(width, Colors::NONE));
	type = TYPE(rand() % 7);
	isFirst = true;
}

bool TetrisGame::Play(vector<vector<Colors>>& gameField, size_t& score, Moves moves) {

	bool isLost = false;
	for (int i = 0; i < 4; i++) {
		auxiliaryField[coords[i].y][coords[i].x] = Colors::NONE;
	}

	Move(moves);

	for (size_t i = 0; i < 4; i++) {
		lastCoords[i] = coords[i];
		coords[i].y += 1;
	}

	if (CheckCollision()) {
		type = TYPE(rand() % 7);
		int newType = (int)type;
		for (int i = 0; i < 4; i++) {
			auxiliaryField[lastCoords[i].y][lastCoords[i].x] = color;
			coords[i].x = figures[newType][i] % 2 + 4;
			coords[i].y = figures[newType][i] / 2;

		}

		//Create new color
		color = Colors(rand() % 7);

		//Check line
		for (size_t i = 4; i < height; i++) {
			bool isLine = true;
			for (size_t j = 0; j < width; j++) {
				if (auxiliaryField[i][j] == Colors::NONE) {
					isLine = false;
					break;
				}
			}

			if (isLine) {
				auxiliaryField.erase(auxiliaryField.begin() + i);
				auxiliaryField.emplace(auxiliaryField.begin(), vector<Colors>(width, Colors::NONE));
				score += 100;
			}
		}

		//Check lose
		isLost = CheckLose();
		//coords[0].x = 0;
	}
	// First block
	if (isFirst) {
		isFirst = false;
		color = Colors(rand() % 7);
		int newType = (int)type;
		for (int i = 0; i < 4; i++) {
			coords[i].x = figures[newType][i] % 2 + 4;
			coords[i].y = figures[newType][i] / 2;
		}
	}

	for (int i = 0; i < 4; i++) {
		auxiliaryField[coords[i].y][coords[i].x] = color;
	}

	for (size_t i = 0; i < gameField.size(); i++) {
		for (size_t j = 0; j < gameField[0].size(); j++) {
			gameField[i][j] = auxiliaryField[i + 4][j];
		}
	}

	return !isLost;
}

void TetrisGame::Preview(vector<vector<Colors>>& gameField) {
	size_t localScore = 0;
	bool isPlaying = Play(gameField, localScore, Moves::NONE);
	if (!isPlaying)
		Reset();
}

size_t TetrisGame::GetDelay() {
	return delay;
}

void TetrisGame::SetDelay(size_t delay) {
	this->delay = delay;
}

bool TetrisGame::CheckCollision() {
	for (int i = 0; i < 4; i++)
		if (coords[i].x < 0 || coords[i].x >= width || coords[i].y >= height)
			return true;
		else if (auxiliaryField[coords[i].y][coords[i].x] != Colors::NONE)
			return true;

	return false;
}

bool TetrisGame::CheckLose() {
	for (size_t i = 0; i < 4; i++)
		if (coords[i] != lastCoords[i])
			return false;

	return true;
}

void TetrisGame::Move(Moves moves) {
	int dx = 0;
	for (int i = 0; i < 4; i++)
		lastCoords[i] = coords[i];

	switch (moves) {
	case Moves::NONE:
		if (maxDelay != delay)
			SetDelay(maxDelay);
		break;
	case Moves::UP:
		Coord p = coords[1];
		for (int i = 0; i < 4; i++) {
			int x = coords[i].y - p.y;
			int y = coords[i].x - p.x;
			coords[i].x = p.x - x;
			coords[i].y = p.y + y;
		}
		break;
	case Moves::DOWN: case Moves::ENTER:
		if (minDelay != delay)
			SetDelay(minDelay);
		break;
	case Moves::RIGHT:
		dx = 1;
		break;
	case Moves::LEFT:
		dx = -1;
		break;
	}
	for (int i = 0; i < 4; i++) {
		coords[i].x += dx;
	}
	if (CheckCollision()) {
		for (int i = 0; i < 4; i++)
			coords[i] = lastCoords[i];
	}
}