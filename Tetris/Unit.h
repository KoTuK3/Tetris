#pragma once
#include <iostream>
#include <vector>

#include "Helpers.h"

using namespace std;

class Unit {
protected:
	size_t x;
	size_t y;

public:
	// This method generate x, y that match the rule
	virtual void GenerateUnit() = 0;
	// This method puts unit on the map
	virtual void PutUnit(vector<vector<bool>>& gameField, bool isCreate) = 0; // if isCreate true we create, else we remove
	virtual void Move(Moves moves);

};
