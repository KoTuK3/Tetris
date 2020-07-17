#include "Snake.h"

Snake::Snake() {
	height = 20;
	width = 10;
	delay = 150;

	Reset();
}

void Snake::Reset() {
	auxiliaryField = vector<vector<bool>>(height, vector<bool>(width, 0));
	snake = SnakePlayer();
	food = SnakeFood();

	snake.PutUnit(auxiliaryField, true);

	food.CreateFood(auxiliaryField);
}

bool Snake::Play(vector<vector<bool>>& gameField, size_t& score, Moves move) {
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

size_t Snake::GetDelay() {
	return delay;
}

void Snake::Preview(vector<vector<bool>>& gameField) {
	size_t localScore = 0;
	Coord coord = snake.GetCoord();
	Moves move = snake.GetMoves();
	Moves nextMove = Moves::NONE;
	if (coord.x == 1 && coord.y == 19) {
		nextMove = Moves::NONE;
	}
	else if (coord.x == 0 && move == Moves::LEFT) {
		nextMove = Moves::UP;
	}
	else if (coord.y == 0 && move == Moves::UP ||
		coord.x == 1 && move == Moves::DOWN) {
		nextMove = Moves::RIGHT;
	}
	else if (coord.x == 1 && move == Moves::LEFT ||
		coord.x == 9 && move == Moves::RIGHT) {
		nextMove = Moves::DOWN;
	}
	else if (coord.x == 9 && move == Moves::DOWN) {
		nextMove = Moves::LEFT;
	}

	Play(gameField, localScore, nextMove);
}