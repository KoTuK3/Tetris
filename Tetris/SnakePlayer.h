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
	Colors color;

public:
	SnakePlayer();

	void GenerateUnit() override;
	void PutUnit(vector<vector<Colors>>& gameField, bool isCreate) override;
	void Move(Moves moves) override;

	void UpdateSnake();
	void AddLength();
	bool CheckCollision();

	void SetMoves(Moves moves);

	Moves GetMoves();
	size_t GetLength();
	Coord GetCoord();
};

