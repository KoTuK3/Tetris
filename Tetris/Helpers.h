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

struct Pixel {
	size_t red;
	size_t green;
	size_t blue;
	size_t alpha;

	bool operator == (const Pixel& pixel) {
		return (
			this->red == pixel.red &&
			this->green == pixel.green &&
			this->blue == pixel.blue &&
			this->alpha == pixel.alpha
		);
	}

	bool operator != (const Pixel& pixel) {
		return (
			this->red != pixel.red ||
			this->green != pixel.green ||
			this->blue != pixel.blue ||
			this->alpha != pixel.alpha
		);
	}
};