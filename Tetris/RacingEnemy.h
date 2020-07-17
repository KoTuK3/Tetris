#pragma once

#include "Unit.h"

class RacingEnemy : public Unit {
private:
	bool side; // false - left, true - right
	
public:
	RacingEnemy() {};
	RacingEnemy(vector<vector<bool>>& auxiliaryField);

	void GenerateUnit() override;
	void PutUnit(vector<vector<bool>>& gameField, bool isCreate) override; //Is create should be true
	void Move(Moves moves) override;

	size_t GetY() const;
	size_t GetX(bool side) const;
	bool GetSide() const;
};