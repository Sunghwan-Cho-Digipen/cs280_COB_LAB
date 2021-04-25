/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Cell.h
Purpose: Source file for Cell
Project: CS230
Author: Kevin Wright
Creation date: 4/26/2020
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/TransformMatrix.h"

#include "Cell.h"
#include "Image_Anims.h"


Cell::Cell(Vector2DInt pos, Images image) : screenPos(pos) {
	sprite = new Sprite("assets/Images.spt");
	sprite->PlayAnimation(static_cast<int>(Images::None));

	SetToImage(image);
}

Cell::~Cell() {
	delete sprite;
}

Vector2DInt Cell::GetPosition() {
	return screenPos;
}

void Cell::Draw() {
	sprite->Draw(TranslateMatrix(screenPos));
}

void Cell::SetToImage(Images image) {
	sprite->PlayAnimation(static_cast<int>(image));
}

Images Cell::GetImage() {
	return static_cast<Images>(sprite->GetAnimation());
}