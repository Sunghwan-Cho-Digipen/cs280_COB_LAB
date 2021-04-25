/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Board.cpp
Purpose: Source file for Board
Project: CS280 Lab 6 - Clash Of Blocks
Author: Kevin Wright, Sunghwan Cho
Creation date: 04/21/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"

#include "Board.h"
#include "Cell.h"
#include "Image_Anims.h"

void Board::Load(std::string fileName)
{
	if (fileName.substr(fileName.find_last_of('.')) != ".dat")
	{
		throw std::runtime_error("Bad Filetype.  " + fileName + " not a sprite info file (.dat)");
	}
	std::ifstream inFile(fileName);
	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to load " + fileName);
	}

	Vector2DInt center = Engine::GetWindow().GetSize() / 2;
	inFile >> boardWidth;
	inFile >> boardHeight;
	Vector2DInt screenPos = { center.x - cellSize.x * (static_cast<int>(boardWidth) - 1) / 2,
						center.y - cellSize.y * (static_cast<int>(boardHeight) - 1) / 2 };

	board = reinterpret_cast<Cell**>(malloc(sizeof(Cell*)* boardHeight + sizeof(Cell) * boardHeight * boardWidth));
	Cell* board_start_ptr = reinterpret_cast<Cell*>(reinterpret_cast<char*>(board) + boardHeight * sizeof(Cell*));
	Cell** header_ptr = nullptr;
	for (int y = 0; y < static_cast<int>(boardHeight); ++y)
	{
		header_ptr = reinterpret_cast<Cell**>(reinterpret_cast<char*>(board) + y * sizeof(Cell*));
		*header_ptr = reinterpret_cast<Cell*>(reinterpret_cast<char*>(board_start_ptr) + boardWidth * y * sizeof(Cell));
	}

	for (int y = 0; y < static_cast<int>(boardHeight); y++)
	{
		for (int x = 0; x < static_cast<int>(boardWidth); x++)
		{
			int frame;
			inFile >> frame;

			if (frame > 1)
			{
				if (IsClash() == true)
				{
					aiStartCells.push_back({ x,y });
				}
				else
				{
					frame = static_cast<int>(Images::None);
				}
			}
			new (&board[y][x]) Cell(screenPos, static_cast<Images>(frame));
			screenPos.x += cellSize.x;
		}
		screenPos.x = center.x - cellSize.x * (boardWidth - 1) / 2;
		screenPos.y += cellSize.y;
	}
}

Board::~Board()
{
	for (int y = 0; y < static_cast<int>(boardHeight); y++)
	{
		for (int x = 0; x < static_cast<int>(boardWidth); x++)
		{
			GetCell({ x, y })->~Cell();		// Yes, I am manually calling the destructor.  
											// This wasn't allocated with a standard new, but we want the destructor called
		}
	}
	free(board);
}

void Board::Draw()
{
	for (int y = 0; y < static_cast<int>(boardHeight); y++)
	{
		for (int x = 0; x < static_cast<int>(boardWidth); x++)
		{
			GetCell({ x, y })->Draw();
		}
	}
}

bool Board::IsMousePosOnBoard(Vector2DInt mousePos)
{
	if (mousePos.x < GetCell({ 0, 0 })->GetPosition().x - cellSize.x)
	{
		return false;
	}
	if (mousePos.y < GetCell({ 0, 0 })->GetPosition().y - cellSize.y)
	{
		return false;
	}
	if (mousePos.x > GetCell({ static_cast<int>(boardWidth) - 1, static_cast<int>(boardHeight) - 1 })->GetPosition().x + cellSize.x / 2)
	{
		return false;
	}
	if (mousePos.y > GetCell({ static_cast<int>(boardWidth) - 1, static_cast<int>(boardHeight) - 1 })->GetPosition().y + cellSize.y / 2)
	{
		return false;
	}
	return true;
}

Vector2DInt Board::MousePosToCellLoction(Vector2DInt mousePos)
{
	if (IsMousePosOnBoard(mousePos) == false)
	{
		Engine::GetLogger().LogError("Mouse pos was in an invalid location");
	}

	Vector2DInt cellLoction = (mousePos - GetCell({ 0, 0 })->GetPosition() + cellSize / 2);

	cellLoction.x /= cellSize.x;
	cellLoction.y /= cellSize.y;
	return cellLoction;
}

Cell* Board::GetCell(Vector2DInt location)
{
	if (location.x < 0 || location.x >= static_cast<int>(boardWidth))
	{
		return nullptr;
	}
	if (location.y < 0 || location.y >= static_cast<int>(boardHeight))
	{
		return nullptr;
	}
	return &board[location.y][location.x];
}