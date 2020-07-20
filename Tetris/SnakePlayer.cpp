#include "SnakePlayer.h"

SnakePlayer::SnakePlayer() {
	moves = Moves::UP;
	GenerateUnit();
}

void SnakePlayer::GenerateUnit() {
	Coord head;
	head.x = x = 5;
	head.y = y = 10;
	lastCoord.x = 0;
	lastCoord.y = 0;
	snake.push_back(head);

	color = Colors::ORANGE;
}

void SnakePlayer::UpdateSnake() {
	lastCoord.x = snake[snake.size() - 1].x;
	lastCoord.y = snake[snake.size() - 1].y;
	snake.pop_back();

	Coord newHead;
	newHead.x = x;
	newHead.y = y;
	auto iter = snake.cbegin();
	snake.insert(iter, newHead);
}

void SnakePlayer::PutUnit(vector<vector<Colors>>& gameField, bool isCreate) {
	Colors localColor = Colors::NONE;
	if (isCreate)
		localColor = color;

	for (size_t i = 0; i < snake.size(); i++)
		gameField[snake[i].y][snake[i].x] = localColor;

	gameField[lastCoord.y][lastCoord.x] = Colors::NONE;
}

void SnakePlayer::Move(Moves moves) {
	switch (moves) {
	case Moves::UP:
		if (GetMoves() != Moves::DOWN) {
			y -= 1;
			SetMoves(moves);
		}
		else {
			Move(GetMoves());
		}
		break;
	case Moves::LEFT:
		if (GetMoves() != Moves::RIGHT) {
			x -= 1;
			SetMoves(moves);
		}
		else {
			Move(GetMoves());
		}
		break;
	case Moves::DOWN:
		if (GetMoves() != Moves::UP) {
			y += 1;
			SetMoves(moves);
		}
		else {
			Move(GetMoves());
		}
		break;
	case Moves::RIGHT:
		if (GetMoves() != Moves::LEFT) {
			x += 1;
			SetMoves(moves);
		}
		else {
			Move(GetMoves());
		}
		break;
	case Moves::NONE:
		Move(GetMoves());
		break;
	}
}

bool SnakePlayer::CheckCollision() {
	if (x < 0 || x >= 10 ||
		y < 0 || y >= 20)
		return true;

	for (size_t i = 1; i < snake.size(); i++)
		if (snake[0] == snake[i])
			return true;

	return false;
}

void SnakePlayer::AddLength() {
	Coord tail;
	tail.x = lastCoord.x;
	tail.y = lastCoord.y;
	snake.push_back(tail);
}

void SnakePlayer::SetMoves(Moves moves) {
	this->moves = moves;
}

Moves SnakePlayer::GetMoves() {
	return moves;
}

size_t SnakePlayer::GetLength() {
	return snake.size();
}

Coord SnakePlayer::GetCoord() {
	return snake[0];
}
