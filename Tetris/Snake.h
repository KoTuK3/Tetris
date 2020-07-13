#pragma once

#include "Game.h"
#include "SnakeFood.h"
#include "SnakePlayer.h"

class Snake : public Game {
private:
	size_t height;
	size_t width;
	size_t delay;
	vector<vector<bool>> auxiliaryField;
	SnakePlayer snake;
	SnakeFood food;

public:
	Snake() {
		height = 20;
		width = 10;
		delay = 150;

		auxiliaryField = vector<vector<bool>>(height, vector<bool>(width, 0));

		snake.PutUnit(auxiliaryField, true);

		food.CreateFood(auxiliaryField);

	}

	bool Play(vector<vector<bool>>& gameField, size_t& score, Moves move) override {
		snake.Move(move);
		if (!snake.CheckCollision()) {
			snake.UpdateSnake();
			snake.PutUnit(auxiliaryField, true);

			if (food.GetCoord() == snake.GetCoord()) {
				food.CreateFood(auxiliaryField);
				snake.AddLength();
			}

			for (size_t i = 0; i < gameField.size(); i++) {
				for (size_t j = 0; j < gameField[0].size(); j++) {
					gameField[i][j] = auxiliaryField[i][j];
				}
			}

			score = (snake.GetLength() - 1) * 100;
		}

		return !snake.CheckCollision();
	}

	size_t GetDelay() override {
		return delay;
	}

	void Preview(vector<vector<bool>>& gameField) override {

	}
};

