#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Game {
public:
	virtual void Play(vector<vector<bool>>& gameField, size_t& score) = 0;
};

