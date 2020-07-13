#pragma once

#include "Unit.h"
#include "Helpers.h"

class SnakePlayer : Unit {
private:
	vector<Coord> snake;
	Coord lastCoord;
	Moves moves;
	int x;
	int y;

public:
	SnakePlayer() {
		moves = Moves::UP;
		GenerateUnit();
	}

	void GenerateUnit() override {
		Coord head;
		head.x = x = 5;
		head.y = y = 10;
		snake.push_back(head);
	}

	void UpdateSnake() {
		lastCoord.x = snake[snake.size() - 1].x;
		lastCoord.y = snake[snake.size() - 1].y;
		snake.pop_back();

		Coord newHead;
		newHead.x = x;
		newHead.y = y;
		auto iter = snake.cbegin();
		snake.insert(iter, newHead);
	}

	void PutUnit(vector<vector<bool>>& gameField, bool isCreate) override {
		for (size_t i = 0; i < snake.size(); i++)
			gameField[snake[i].y][snake[i].x] = true;

		gameField[lastCoord.y][lastCoord.x] = false;
	}

	void Move(Moves moves) override {
		switch (moves) {
		case Moves::UP:
			if (GetMoves() != Moves::DOWN) {
				y -= 1;
				SetMoves(moves);
			}
			break;
		case Moves::LEFT:
			if (GetMoves() != Moves::RIGHT) {
				x -= 1;
				SetMoves(moves);
			}
			break;
		case Moves::DOWN:
			if (GetMoves() != Moves::UP) {
				y += 1;
				SetMoves(moves);
			}
			break;
		case Moves::RIGHT:
			if (GetMoves() != Moves::LEFT) {
				x += 1;
				SetMoves(moves);
			}
			break;
		case Moves::NONE:
			Move(GetMoves());
			break;
		}
	}

	bool CheckCollision() {
		if (x < 0 || x >= 10 ||
			y < 0 || y >= 20)
			return true;

		for (size_t i = 1; i < snake.size(); i++)
			if (snake[0] == snake[i])
				return true;

		return false;
	}

	void AddLength() {
		Coord tail;
		tail.x = lastCoord.x;
		tail.y = lastCoord.y;
		snake.push_back(tail);
	}

	void SetMoves(Moves moves) {
		this->moves = moves;
	}

	Moves GetMoves() {
		return moves;
	}

	size_t GetLength() {
		return snake.size();
	}

	Coord GetCoord() {
		return snake[0];
	}
};

