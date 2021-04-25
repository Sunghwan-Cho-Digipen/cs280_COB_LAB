/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: board.h
Purpose: Header file for Board
Project: CS230
Author: Kevin Wright
Creation date: 4/30/2020
-----------------------------------------------------------------*/

#pragma once
#include <list>

#include "..\Engine\BasicDataTypes.h"

class Cell;

class Board {
public:
	virtual ~Board();
	void Load(std::string fileName);
	void Draw();

	bool IsMousePosOnBoard(Vector2DInt mousePos);
	Vector2DInt MousePosToCellLoction(Vector2DInt mousePos);
	virtual bool IsClash() { return false; }
	Cell* GetCell(Vector2DInt location);

protected:
	std::list<Vector2DInt> aiStartCells;

private:
	int stepValue;
	Cell** board;
	unsigned int boardWidth;
	unsigned int boardHeight;
	static constexpr Vector2DInt cellSize = { 64,64 };
};