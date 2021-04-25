/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ClashOfBlocks.cpp
Purpose: Source file for ClashOfBlocks
Project: CS280 Lab 6 - Clash Of Blocks
Author: Sunghwan Cho
Creation date: 04/25/2021
-----------------------------------------------------------------*/

#include "ClashOfBlocks.h"
#include "Cell.h"
#include "Image_Anims.h"

bool ClashOfBlocks::Visit()
{
	if (toVisit.empty() == false)
	{
		const int TO_VISIT_SIZE = static_cast<int>(toVisit.size());
		
		for (int i = 0; i < TO_VISIT_SIZE; ++i)
		{
			
			const Vector2DInt CURRENT_POSITION = toVisit.front().cellPos;
			const int CURRENT_STEP = toVisit.front().step;
			const Images IMAGE_OF_PLAYER = toVisit.front().imageToUse;
			toVisit.pop_front();

			Cell* cell = board->GetCell(CURRENT_POSITION);

			if (CURRENT_STEP != 0 && cell->GetImage() != Images::None)
			{
				continue;
			}

			cell->SetToImage(IMAGE_OF_PLAYER);

			const ToVisit UPWARD{ CURRENT_POSITION + Vector2DInt{ 0,1 },CURRENT_STEP + 1 ,IMAGE_OF_PLAYER };
			const ToVisit RIGHTWARD{ CURRENT_POSITION + Vector2DInt{ 1,0 },CURRENT_STEP + 1 ,IMAGE_OF_PLAYER };
			const ToVisit DOWNWARD{ CURRENT_POSITION + Vector2DInt{ 0,-1 },CURRENT_STEP + 1 ,IMAGE_OF_PLAYER };
			const ToVisit LEFTWARD{ CURRENT_POSITION + Vector2DInt{ -1,0 },CURRENT_STEP + 1 ,IMAGE_OF_PLAYER };
			
			if (TryToAdd(UPWARD) == true)
			{
				toVisit.emplace_back(UPWARD);
			}

			if (TryToAdd(RIGHTWARD) == true)
			{
				toVisit.emplace_back(RIGHTWARD);
			}
			
			if (TryToAdd(DOWNWARD) == true)
			{
				toVisit.emplace_back(DOWNWARD);
			}
			
			if (TryToAdd(LEFTWARD) == true)
			{
				toVisit.emplace_back(LEFTWARD);
			}
			
		}

		return false;
	}

	return true;
}

void ClashOfBlocks::PlayerSelected(Vector2DInt cellLocation)
{
	toVisit.clear();
	Cell* currentCell = board->GetCell(cellLocation);
	currentCell->SetToImage(Images::RedX);
	toVisit.emplace_back(ToVisit{ cellLocation ,0,Images::Red });

	for (const Vector2DInt& AI_POSITION : board->GetAIStartSpots())
	{
		const Images IMAGE_OF_AI = static_cast<Images>(static_cast<int>(board->GetCell(AI_POSITION)->GetImage()) - 1); // from the assignment explanation
		toVisit.emplace_back(ToVisit{ AI_POSITION ,0,IMAGE_OF_AI });
	}
}

bool ClashOfBlocks::TryToAdd(ToVisit tryToAdd)
{
	Cell* cell = board->GetCell(tryToAdd.cellPos);
	
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

