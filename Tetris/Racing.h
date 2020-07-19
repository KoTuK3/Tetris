#pragma once
#include "Game.h"
#include "RacingPlayer.h"
#include "RacingEnemy.h"
#include "Tetris.h"

class Racing : public Game {
private:
	size_t height;
	size_t width;
	size_t delay;
	size_t counter;
	size_t dist;

	vector<vector<Colors>> auxiliaryField;

	RacingPlayer player;
	vector<RacingEnemy> enemies;

	Colors wallsColor;

public:
	Racing();

	void Reset() override;
	bool Play(vector<vector<Colors>>& gameField, size_t& score, Moves moves) override;
	void Preview(vector<vector<Colors>>& gameField) override;

	bool CheckCollision();
	bool CheckDist();

	size_t GetDelay() override;
	void SetDelay(size_t delay);
};

