#pragma once

#include "Unit.h"
#include "Helpers.h"

class RacingPlayer : public Unit {
private:
	bool side; // false - left, true - right
	bool lastSide;

	size_t delay; // For speed
	size_t minDelay;
	size_t maxDelay;
	Colors color;

public:
	RacingPlayer() {}
	RacingPlayer(vector<vector<Colors>>& auxiliaryField);

	void GenerateUnit() override;
	void PutUnit(vector<vector<Colors>>& gameField, bool isCreate) override;
	void Move(Moves moves) override;

	bool GetSide() const;
	bool GetLastSide() const;
	size_t GetX(bool side) const;
	size_t GetDelay() const;

	void SetLastSide(bool side);
	void SetDelay(size_t delay);
};