#define _WIN32_WINNT 0x0500

#include "Tetris.h"
#include "Racing.h"
#include "Snake.h"
#include "Game.h"

#include "SFML/Graphics.hpp"

Tetris::Tetris() {
	height = 20;
	width = 10;

	gameField = vector<vector<Colors>>(height, vector<Colors>(width, Colors::NONE));
	display = vector<vector<Colors>>(height, vector<Colors>(width, Colors::NONE));

	score = 0;
	lastScore = 1;

	pixelSize = 36;
	texturePixelSize = 18;

	isPlaying = false;
}

void Tetris::ShowChar(int x, int y, char character) {
	COORD cord;
	cord.X = x;
	cord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	cout << character;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void Tetris::ShowString(int x, int y, string str) {
	COORD cord;
	cord.X = x;
	cord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	cout << str;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

bool Tetris::IsUpdate() {
	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
			if (display[i][j] != gameField[i][j])
				return true;

	if (score != lastScore)
		return true;

	return false;
}

Moves Tetris::Move() {
	if (_kbhit()) {
		switch (_getch()) {
			//w = 119; W = 87; Up arrow = 72
		case 119: case 87: case 72:
			return Moves::UP;
			break;
			//a = 97; A = 65; Left arrow = 75
		case 97: case 65: case 75:
			return Moves::LEFT;
			break;
			//s = 115; S = 83; Down arrow = 80
		case 115: case 83: case 80:
			return Moves::DOWN;
			break;
			//d = 100; D = 68; Right arrow = 77
		case 100: case 68: case 77:
			return Moves::RIGHT;
			break;
			//Enter
		case 32: case 13:
			return Moves::ENTER;
			break;
		}
	}
	return Moves::NONE;
}

Moves Tetris::Move(int key) {
	switch (key) {
		case Keyboard::W: case Keyboard::Up:
			return Moves::UP;
			break;
		case Keyboard::A: case Keyboard::Left:
			return Moves::LEFT;
			break;
		case Keyboard::S: case Keyboard::Down:
			return Moves::DOWN;
			break;
		case Keyboard::D: case Keyboard::Right:
			return Moves::RIGHT;
			break;
		case Keyboard::Space: case Keyboard::Enter:
			return Moves::ENTER;
			break;
	}
	return Moves::NONE;
}

void Tetris::Play(int index) {
	if (index >= 0 && index < games.size()) {
		bool isLose = true;
		do {
			isLose = games[index]->Play(gameField, score, Move());
			//games[index]->Preview(gameField);
			Update();
			Sleep(games[index]->GetDelay());
		} while (isLose);
		Reset(index);
	}
}

void Tetris::Play(RenderWindow& window, Sprite& sprite, Text& text, int index) {
	if (index >= 0 && index < games.size()) {
		bool isLose = true;
		do {
			isLose = games[index]->Play(gameField, score, Move());
			Update(window, sprite, text);
			Sleep(games[index]->GetDelay());
		} while (isLose);

		Reset(window, index);
	}
}

void Tetris::PlayingMode(RenderWindow& window, Sprite& sprite, Moves move, int index) {
	if (index >= 0 && index < games.size()) {
		bool isLose = true;
		isLose = games[index]->Play(gameField, score, move);
		Sleep(games[index]->GetDelay());

		if (isLose)
			isPlaying = true;
		else {
			Reset(window, index);
			isPlaying = false;
			isAnimation = true;
		}
	}
}

void Tetris::Preview(int index) {
	if (index >= 0 && index < games.size()) {
		games[index]->Preview(gameField);
		Update();
		Sleep(games[index]->GetDelay());
	}
}

void Tetris::Reset(int index) {
	ClearDisplay();
	games[index]->Reset();
	score = 0;
	lastScore = 1;
}

void Tetris::Reset(RenderWindow& window, int index) {
	ClearDisplay(window);
	games[index]->Reset();
	score = 0;
	lastScore = 1;
}

void Tetris::Menu() {
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo);

	system("mode con cols=150 lines=50");

	// Start preview
	ClearDisplay();

	Animation();

	int index = 0;
	Moves move;
	do {
		Preview(index);

		move = Move();
		switch (move) {
			case Moves::RIGHT:
				Reset(index);
				index += 1;
				break;
			case Moves::LEFT:
				Reset(index);
				index -= 1;
				break;
			case Moves::ENTER:
				Reset(index);
				Animation();
				Play(index);
				Reset(index);
				Animation();
				break;
			case Moves::NONE:
				break;
		}
		if (index == -1)
			index = games.size() - 1;
		else if (index == games.size())
			index = 0;

	} while (true);
}

void Tetris::MenuSFML() {
	//Test
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	RenderWindow window(VideoMode(500, 720), "Tetris");

	Vector2f backgroundSize(pixelSize * width, pixelSize * height);
	Vector2f spriteSize(pixelSize, pixelSize);

	Font font;
	Texture texture, textureBackground;
	texture.loadFromFile(".\\images\\tiles.png");
	textureBackground.loadFromFile(".\\images\\background.png");

	//Sprites
	Sprite sprite(texture), spriteBackground(textureBackground);

	font.loadFromFile(".\\font\\Grand9K Pixel.ttf");

	Text text("Score: \n000000", font, 25);
	text.setPosition(pixelSize * width + 15, 30);
	

	spriteBackground.setScale(
		backgroundSize.x / spriteBackground.getLocalBounds().width,
		backgroundSize.y / spriteBackground.getLocalBounds().height
	);

	Moves move = Moves::NONE;

	int index = 0;

	size_t i, j;
	i = j = 0;
	animColor = Colors(rand() % 7);
	isAnimation = true;

	while (window.isOpen()) {
		Event event;
		move = Moves::NONE;


		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::KeyPressed) {
				move = Move(event.key.code);
			}
		}

		if (isAnimation) {
			Animation(window, index, i, j);
		}
		else if (isPlaying) {
			PlayingMode(window, sprite, move, index);
		}
		else {
			MenuMode(window, sprite, move, index);
			Preview(index);
		}

		window.clear(Color(30, 30, 60, 0));
		window.draw(spriteBackground);
		window.draw(text);

		Update(window, sprite, text);
	}
}

void Tetris::MenuMode(RenderWindow& window, Sprite& sprite, Moves move, int& index) {
	switch (move) {
		case Moves::RIGHT:
			Reset(window, index);
			index += 1;
			break;
		case Moves::LEFT:
			Reset(window, index);
			index -= 1;
			break;
		case Moves::ENTER:
			isAnimation = true;
			isPlaying = true;
			break;
	}
	if (index == -1)
		index = games.size() - 1;
	else if (index == games.size())
		index = 0;
}

void Tetris::ClearDisplay(RenderWindow& window) {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = Colors::NONE;
		}
	}

	window.clear(Color(30, 30, 60, 0));
}

void Tetris::ClearDisplay() {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = Colors::NONE;
			ShowChar(j * 2, i, 176);
			ShowChar(j * 2 + 1, i, 176);
		}
	}
	Update();
}

void Tetris::Animation() {
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			gameField[i][j] = animColor;
			Update();
			Sleep(10);
		}
	}
}

void Tetris::Animation(RenderWindow& window, int index, size_t& i,size_t& j) {
	if (i == height - 1 && j == width - 1) {
		gameField[i][j] = animColor;
		isAnimation = false;
		animColor = Colors(rand() % 7);
		i = j = 0;
		Reset(window, index);
	}
	else if (j == width - 1) {
		gameField[i][j] = animColor;
		j = 0;
		i += 1;
	}
	else {
		gameField[i][j] = animColor;
		j += 1;
	}

	Sleep(10);
}

void Tetris::Update() {
	bool isUpdated = false;
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (display[i][j] != gameField[i][j]) {
				isUpdated = true;
				display[i][j] = gameField[i][j];
				if (display[i][j] != Colors::NONE) {
					ShowChar(j * 2, i, 219);
					ShowChar(j * 2 + 1, i, 219);
				}
				else {
					ShowChar(j * 2, i, 176);
					ShowChar(j * 2 + 1, i, 176);
				}
			}
		}
		if (isUpdated)
			cout << endl;
	}

	if (score != lastScore) {
		lastScore = score;
		string str = to_string(score);

		while (str.length() < 6) {
			str = '0' + str;
		}

		ShowString((width + 1) * 2, 0, "Score:");
		ShowString((width + 1) * 2, 1, str);
	}
}

void Tetris::Update(RenderWindow& window, Sprite& sprite, Text& text) {

	Vector2f spriteSize(pixelSize, pixelSize);
	sprite.setScale(
		spriteSize.x / sprite.getLocalBounds().width,
		spriteSize.y / sprite.getLocalBounds().height
	);

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			if (gameField[i][j] != Colors::NONE) {
				sprite.setTextureRect(IntRect(texturePixelSize * int(gameField[i][j]), 0, texturePixelSize, texturePixelSize));
				sprite.setPosition(j * pixelSize, i * pixelSize);
				window.draw(sprite);
			}
		}
	}
	//Add score
	if (score != lastScore) {
		lastScore = score;
		string str = to_string(score);

		while (str.length() < 6) {
			str = '0' + str;
		}
		text.setString("Score: \n" + str);
	}

	window.display();
}

void Tetris::AddGame(Game* game) {
	games.push_back(game);
}