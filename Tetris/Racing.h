#pragma once
#include <Windows.h>
#include "Game.h"
#include "RacingPlayer.h"
#include "RacingEnemy.h"

class Racing : Game {
private:
	size_t height;
	size_t width;
	size_t delay;

	vector<vector<bool>> auxiliaryField;

	RacingPlayer player;
	vector<RacingEnemy> enemies;

public:
	Racing() {
		height = 24;
		width = 10;

		delay = 50;

		auxiliaryField = vector<vector<bool>>(height, vector<bool>(width, 0));
	}

	void Play(vector<vector<bool>>& gameField, size_t& score) override {
		do {



			Sleep(delay);
		} while (true);
	}

};

