#pragma once
#define NOMINMAX
#include <iostream>
#include <vector>
#include <Windows.h>

#include "Helpers.h"

using namespace std;

class Game {
public:
	virtual bool Play(vector<vector<Colors>>& gameField, size_t& score, Moves move) = 0;
	virtual size_t GetDelay() = 0;
	virtual void Preview(vector<vector<Colors>>& gameField) = 0;
	virtual void Reset() = 0;
};

