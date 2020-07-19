#include "Racing.h"

Racing::Racing() {
	height = 24;
	width = 10;

	delay = 80;

	dist = 9;

	Reset();
}

void Racing::Reset() {
	wallsColor = Colors::YELLOW;

	counter = 0;
	auxiliaryField = vector<vector<Colors>>(height, vector<Colors>(width, Colors::NONE));

	//Generate walls
	for (int i = 0; i < height; i++) {
		if (i % 4 != 0) {
			auxiliaryField[i][0] =
			auxiliaryField[i][width - 1] = wallsColor;
		}
	}

	enemies.clear();
	player = RacingPlayer(auxiliaryField);
	RacingEnemy enemy(auxiliaryField);
	enemies.push_back(enemy);
}

bool Racing::CheckCollision() {
	if (enemies[0].GetSide() == player.GetSide() && enemies[0].GetY() > 18)
		return true;
	return false;
}

bool Racing::Play(vector<vector<Colors>>& gameField, size_t& score, Moves moves) {
	bool isWall = false;
	if (auxiliaryField[height - 1][0] == Colors::NONE) {
		isWall = false;
	}
	else {
		isWall = true;
	}

	player.PutUnit(auxiliaryField, false);

	player.Move(moves);
	SetDelay(player.GetDelay());

	if (player.GetLastSide() != player.GetSide()) {
		player.PutUnit(auxiliaryField, false);
		player.SetLastSide(player.GetSide());
	}

	auxiliaryField.pop_back();
	vector<Colors> newRow(width, Colors::NONE);

	if (isWall)
		newRow[0] = newRow[width - 1] = wallsColor;
	else
		newRow[0] = newRow[width - 1] = Colors::NONE;

	auxiliaryField.insert(auxiliaryField.begin(), newRow);

	if (CheckDist()) {
		RacingEnemy enemy(auxiliaryField);
		enemies.push_back(enemy);
	}

	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i].Move(Moves::DOWN);
	}

	if (enemies[0].GetY() >= 27) {
		enemies.erase(enemies.begin());
	}

	if (enemies[0].GetY() == 23) {
		score += 10;
	}

	//generateCart();
	player.PutUnit(auxiliaryField, true);

	for (size_t i = 0; i < gameField.size(); i++) {
		for (size_t j = 0; j < gameField[0].size(); j++) {
			gameField[i][j] = auxiliaryField[i + 4][j];
		}
	}

	return !CheckCollision(); // check for lost
}

void Racing::Preview(vector<vector<Colors>>& gameField) {
	size_t localScore = 0;
	Moves move = Moves::NONE;

	if (enemies[0].GetSide() == player.GetSide() && enemies[0].GetY() >= 17) {
		if (player.GetSide() == false)
			move = Moves::RIGHT;
		else if (player.GetSide() == true)
			move = Moves::LEFT;
	}

	Play(gameField, localScore, move);
}

bool Racing::CheckDist() {
	if (counter < dist) {
		counter++;
		return false;
	}
	else {
		dist = rand() % 3 + 9;
		counter = 0;
		return true;
	}
}

size_t Racing::GetDelay() {
	return delay;
}

void Racing::SetDelay(size_t delay) {
	this->delay = delay;
}
