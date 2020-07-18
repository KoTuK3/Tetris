#pragma once

#include "Game.h"
#include "Helpers.h"

enum class TYPE {
	I,
	S,
	Z,
	T,
	L,
	J,
	O
};

class TetrisGame : public Game {
private:

	vector<vector<bool>> auxiliaryField;
	vector<vector<int>> figures;

	size_t height;
	size_t width;
	size_t delay, minDelay, maxDelay;

	Coord point;
	Coord coords[4];
	Coord lastCoords[4];

	TYPE type;
	bool isFirst;
public:
	TetrisGame() {
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

	void Reset() override {
		auxiliaryField = vector<vector<bool>>(height, vector<bool>(width, false));
		type = TYPE(rand() % 7);
		isFirst = true;
	}

	bool Play(vector<vector<bool>>& gameField, size_t& score, Moves moves) override {
		bool isLost = false;
		for (int i = 0; i < 4; i++) {
			auxiliaryField[coords[i].y][coords[i].x] = false;
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
				auxiliaryField[lastCoords[i].y][lastCoords[i].x] = true;
				coords[i].x = figures[newType][i] % 2 + 4;
				coords[i].y = figures[newType][i] / 2;

			}

			//Check line
			for (size_t i = 4; i < height; i++) {
				bool isLine = true;
				for (size_t j = 0; j < width; j++) {
					if (auxiliaryField[i][j] == false) {
						isLine = false;
						break;
					}
				}

				if (isLine) {
					auxiliaryField.erase(auxiliaryField.begin() + i);
					auxiliaryField.emplace(auxiliaryField.begin(), vector<bool>(width, false));
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
			int newType = (int)type;
			for (int i = 0; i < 4; i++) {
				coords[i].x = figures[newType][i] % 2 + 4;
				coords[i].y = figures[newType][i] / 2;
			}
		}

		for (int i = 0; i < 4; i++) {
			auxiliaryField[coords[i].y][coords[i].x] = true;
		}

		for (size_t i = 0; i < gameField.size(); i++) {
			for (size_t j = 0; j < gameField[0].size(); j++) {
				gameField[i][j] = auxiliaryField[i + 4][j];
			}
		}

		//Test
		return !isLost;

	}

	void Move(Moves moves) {
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

	void Preview(vector<vector<bool>>& gameField) override {

	}

	size_t GetDelay() override {
		return delay;
	}

	void SetDelay(size_t delay) {
		this->delay = delay;
	}

	bool CheckCollision() {
		for (int i = 0; i < 4; i++)
			if (coords[i].x < 0 || coords[i].x >= width || coords[i].y >= height)
				return true;
			else if (auxiliaryField[coords[i].y][coords[i].x])
				return true;

		return false;
	}

	bool CheckLose() {
		for (size_t i = 0; i < 4; i++)
			if (coords[i] != lastCoords[i])
				return false;
		
		return true;
	}

};

