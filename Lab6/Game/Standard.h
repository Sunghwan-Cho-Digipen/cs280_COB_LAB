/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Standard.cpp
Purpose: Source file for Standard
Project: CS230
Author: Kevin Wright
Creation date: 5/13/2020
-----------------------------------------------------------------*/

#pragma once
#include <list>

#include "Level.h"
#include "Board.h"

class Texture;
class Sprite;

class Standard : public Level {
public:
	void MakeBoard(std::string levelData) override { board = new Board(); board->Load(levelData); }
	Board* GetBoard() override { return board; }
	bool Visit() override;
	void PlayerSelected(Vector2DInt cellLocation) override;
	std::string GetName() override { return "SlowFill " + std::to_string(currLevel); }
private:
	bool TryToAdd(Vector2DInt cellPos);

	Board* board;
	std::list<Vector2DInt> toVisit;
};

