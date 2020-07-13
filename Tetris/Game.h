#pragma once
#include <iostream>
#include <vector>

#include "Helpers.h"

using namespace std;

class Game {
public:
	virtual bool Play(vector<vector<bool>>& gameField, size_t& score, Moves move) = 0;
	virtual size_t GetDelay() = 0;
	virtual void Preview(vector<vector<bool>>& gameField) = 0;
};

