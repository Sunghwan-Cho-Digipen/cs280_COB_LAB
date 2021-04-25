/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Cell.h
Purpose: Header file for Cell
Project: CS230
Author: Kevin Wright
Creation date: 4/26/2020
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\BasicDataTypes.h"

class Sprite;
enum class Images;

class Cell {
public:
	Cell(Vector2DInt pos, Images image);
	~Cell();
	Vector2DInt GetPosition();
	void Draw();
	void SetToImage(Images image);
	Images GetImage();
private:
	Vector2DInt screenPos;
	Sprite* sprite;
};