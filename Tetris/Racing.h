#pragma once
#include <Windows.h>
#include "Game.h"
#include "RacingPlayer.h"
#include "RacingEnemy.h"
#include "Tetris.h"

class Racing : public Game {
private:
	size_t height;
	size_t width;
	size_t delay;
	size_t counter;
	size_t dist;

	vector<vector<bool>> auxiliaryField;

	RacingPlayer player;
	vector<RacingEnemy> enemies;

public:
	Racing() {
		height = 24;
		width = 10;

		delay = 80;

		counter = 0;
		dist = 9;

		auxiliaryField = vector<vector<bool>>(height, vector<bool>(width, 0));

		//Generate walls
		for (int i = 0; i < height; i++) {
			if (i % 4 != 0) {
				auxiliaryField[i][0] = 1;
				auxiliaryField[i][width - 1] = 1;
			}
		}

		player = RacingPlayer(auxiliaryField);
		RacingEnemy enemy(auxiliaryField);
		enemies.push_back(enemy);
	}

	bool CheckCollision() {
		if (enemies[0].GetSide() == player.GetSide() && enemies[0].GetY() > 18) 
			return true;
		return false;
	}
	//Test moves
	bool Play(vector<vector<bool>>& gameField, size_t& score, Moves moves) override {
			
		bool isWall = auxiliaryField[height - 1][0];

		player.PutUnit(auxiliaryField, false);

		player.Move(moves);
		SetDelay(player.GetDelay());

		if (player.GetLastSide() != player.GetSide()) {
			player.PutUnit(auxiliaryField, false);
			player.SetLastSide(player.GetSide());
		}

		auxiliaryField.pop_back();
		vector<bool> newRow(width, 0);
		newRow[0] = newRow[width - 1] = isWall;
		auxiliaryField.insert(auxiliaryField.begin(), newRow);

		if (CheckDist()) {
			RacingEnemy enemy(auxiliaryField);
			enemies.push_back(enemy);
		}

		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i].Move(Moves::DOWN);
		}

		if (enemies[0].GetY() >= 27) {
			enemies.erase(enemies.begin());
		}

		if (enemies[0].GetY() == 23) {
			score++;
		}

		//generateCart();
		player.PutUnit(auxiliaryField, true);

		for (size_t i = 0; i < gameField.size(); i++) {
			for (size_t j = 0; j < gameField[0].size(); j++) {
				gameField[i][j] = auxiliaryField[i + 4][j];
			}
		}

		return !CheckCollision(); // check for lost
	}

	void Preview(vector<vector<bool>>& gameField) override {
		size_t localScore = 0;
		Moves move = Moves::NONE;

		if (enemies[0].GetSide() == player.GetSide() && enemies[0].GetY() >= 17) {
			if (player.GetSide() == false)
				move = Moves::RIGHT;
			else if (player.GetSide() == true)
				move = Moves::LEFT;
		}
		
		Play(gameField, localScore, move);
		Sleep(delay);
	}

	bool CheckDist() {
		if (counter < dist) {
			counter++;
			return false;
		}
		else {
			dist = rand() % 3 + 9;
			counter = 0;
			return true;
		}
	}

	size_t GetDelay() override {
		return delay;
	}

	void SetDelay(size_t delay) {
		this->delay = delay;
	}
};

