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

	vector<vector<Colors>> auxiliaryField;
	vector<vector<int>> figures;

	size_t height;
	size_t width;
	size_t delay, minDelay, maxDelay;

	Coord point;
	Coord coords[4];
	Coord lastCoords[4];

	TYPE type;
	bool isFirst;

	Colors color;

public:
	TetrisGame();

	void Reset() override;
	bool Play(vector<vector<Colors>>& gameField, size_t& score, Moves moves) override;
	void Preview(vector<vector<Colors>>& gameField) override;
	void Move(Moves moves);

	bool CheckCollision();
	bool CheckLose();

	size_t GetDelay() override;
	void SetDelay(size_t delay);
};

