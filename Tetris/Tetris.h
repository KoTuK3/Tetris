#pragma once
#define NOMINMAX

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>

#include "SFML/Graphics.hpp"

#include "Game.h"
#include "Helpers.h"

using namespace std;
using namespace sf;


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

	vector<Game*> games;

	size_t pixelSize;
	size_t texturePixelSize;
	
	void ShowChar(int x, int y, char character);
	void ShowString(int x, int y, string str);
	bool IsUpdate();
	Moves Move();
	Moves Move(int key);

	//Test
	bool isPlaying;

public:
	Tetris();
	void Update();
	void Update(RenderWindow& window, Sprite& sprite);
	void AddGame(Game* game);
	void Play(int index);
	void Play(RenderWindow& window, Sprite& sprite, int index);
	void PlayingMode(RenderWindow& window, Sprite& sprite, Moves move, int index);
	void Preview(int index);
	void Reset(int index);
	void Reset(RenderWindow& window, Sprite& sprite, int index);
	void Menu();
	void MenuSFML();
	void MenuMode(RenderWindow& window, Sprite& sprite, Moves move, int& index);
	void ClearDisplay();
	void ClearDisplay(RenderWindow& window, Sprite& sprite);
	void Animation();
	void Animation(RenderWindow& window, Sprite& sprite);
};

