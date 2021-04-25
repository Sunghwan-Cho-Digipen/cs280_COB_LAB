/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Standard.cpp
Purpose: Source file for Standard
Project: CS280 Lab 6 - Clash Of Blocks
Author: Sunghwan Cho
Creation date: 04/25/2021
-----------------------------------------------------------------*/

#include "Standard.h"
#include "../Engine/Sprite.h"
#include "Cell.h"
#include "Image_Anims.h"


bool Standard::Visit()
{
	if (toVisit.empty() == false)
	{
		const Vector2DInt CURRENT_POSITION = toVisit.front();
		toVisit.pop_front();
		Cell* currentCell = board->GetCell(CURRENT_POSITION);
		currentCell->SetToImage(Images::Red);

		const Vector2DInt UPWARD = CURRENT_POSITION + Vector2DInt{ 0,1 };
		const Vector2DInt RIGHTWARD = CURRENT_POSITION + Vector2DInt{ 1,0 };
		const Vector2DInt DOWNWARD = CURRENT_POSITION + Vector2DInt{ 0,-1 };
		const Vector2DInt LEFTWARD = CURRENT_POSITION + Vector2DInt{ -1,0 };

		if (TryToAdd(UPWARD) == true)
		{
			board->GetCell(UPWARD)->SetToImage(Images::RedX);
			toVisit.push_back(UPWARD);
		}

		if (TryToAdd(RIGHTWARD) == true)
		{
			board->GetCell(RIGHTWARD)->SetToImage(Images::RedX);
			toVisit.push_back(RIGHTWARD);
		}

		if (TryToAdd(DOWNWARD) == true)
		{
			board->GetCell(DOWNWARD)->SetToImage(Images::RedX);
			toVisit.push_back(DOWNWARD);
		}

		if (TryToAdd(LEFTWARD) == true)
		{
			board->GetCell(LEFTWARD)->SetToImage(Images::RedX);
			toVisit.push_back(LEFTWARD);
		}

		return false;
	}
	return true;
}

void Standard::PlayerSelected(Vector2DInt cellLocation)
{
	toVisit.clear();
	Cell* selectedCell = board->GetCell(cellLocation);
	selectedCell->SetToImage(Images::RedX);
	toVisit.push_back(cellLocation);
}

bool Standard::TryToAdd(Vector2DInt cellPos)
{
	Cell* cell = board->GetCell(cellPos);
	if (cell == nullptr)
	{
		return false;
	}

	if (cell->GetImage() != Images::None)
	{
		return false;
	}

	return true;
}
