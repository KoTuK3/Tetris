#pragma once
#include <Windows.h>
#include "Game.h"

class Enemy {

};

class Player {

};

class Racing : Game {
private:
	size_t height;
	size_t width;
	size_t delay;

	vector<vector<bool>> auxiliaryField;

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

