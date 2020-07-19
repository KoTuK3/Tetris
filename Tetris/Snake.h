#pragma once

#include "Game.h"
#include "SnakeFood.h"
#include "SnakePlayer.h"

class Snake : public Game {
private:
	size_t height;
	size_t width;
	size_t delay;
	vector<vector<Colors>> auxiliaryField;
	SnakePlayer snake;
	SnakeFood food;

public:
	Snake();

	void Reset() override;
	bool Play(vector<vector<Colors>>& gameField, size_t& score, Moves move) override;
	void Preview(vector<vector<Colors>>& gameField) override;
	size_t GetDelay() override;
};

