/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ClashOfBlocks.h
Purpose: Header file for ClashOfBlocks
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
enum class Images;

class ClashOfBlocks : public Level {
private:
	struct ToVisit;

public:
	void MakeBoard(std::string levelData) override { board = new ClashBoard(levelData); }
	Board* GetBoard() override { return board; }
	bool Visit() override;
	void PlayerSelected(Vector2DInt cellLocation) override;

	std::string GetName() override { return "ClashOfBlocks " + std::to_string(currLevel); }
private:
	bool TryToAdd(ToVisit tryToAdd);

	class ClashBoard : public Board {
	public:
		ClashBoard(std::string levelData) { Load(levelData); }
		bool IsClash() override { return true; }
		std::list<Vector2DInt> GetAIStartSpots() { return aiStartCells; }
	private:
	};
	ClashBoard* board;

	struct ToVisit {
		Vector2DInt cellPos;
		int step;
		Images imageToUse;
	};

	std::list<ToVisit> toVisit;
};

