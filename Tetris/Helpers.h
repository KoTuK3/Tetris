#pragma once

enum class Moves {
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ENTER
};

struct Coord {
	size_t x;
	size_t y;

	bool operator == (const Coord& coord) const {
		return (this->x == coord.x && this->y == coord.y);
	}

	bool operator != (const Coord& coord) const {
		return (this->x != coord.x || this->y != coord.y);
	}
};