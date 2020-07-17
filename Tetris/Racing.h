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

	vector<vector<bool>> auxiliaryField;

	RacingPlayer player;
	vector<RacingEnemy> enemies;

public:
	Racing();

	void Reset() override;
	bool Play(vector<vector<bool>>& gameField, size_t& score, Moves moves) override;
	void Preview(vector<vector<bool>>& gameField) override;

	bool CheckCollision();
	bool CheckDist();

	size_t GetDelay() override;
	void SetDelay(size_t delay);
};

