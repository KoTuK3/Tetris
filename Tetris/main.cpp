#include <iostream>
#include <ctime>

#include "Tetris.h"

using namespace std;

int main() {
	srand((unsigned)time(nullptr));
	Tetris tetris;

	tetris.Play();
	return 0;
}