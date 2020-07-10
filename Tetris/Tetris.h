#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>

#include "Game.h"
#include "Helpers.h"

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

	vector<Game> games;
	
	void ShowChar(int x, int y, char character);
	void ShowString(int x, int y, string str);
	bool IsUpdate();
	Moves Move();

public:
	Tetris();
	void Update();
	void Play();

};

