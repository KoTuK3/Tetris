#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "windows.h"

using namespace std;

class Tetris {
private:
	// Display size in pixels
	size_t height;
	size_t width;

	size_t score; // this score we can change
	size_t lastScore;

	vector<vector<bool>> gameField; // this field we can change
	// display id used for output to the console
	vector<vector<bool>> display;
	
	void ShowChar(int x, int y, char character);
	void ShowString(int x, int y, string str);

public:
	Tetris();
	void Update();
};

