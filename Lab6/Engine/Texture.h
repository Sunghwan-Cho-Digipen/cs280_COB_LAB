/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <doodle/image.hpp>	//doodle::Image
#include "BasicDataTypes.h"

class TransformMatrix;

class Texture {
	friend class TextureManager;
	friend class SpriteFont;
public:
	Texture() {}
	void Draw(TransformMatrix displayMatrix);
	void Draw(TransformMatrix displayMatrix, Vector2DInt texelPos, Vector2DInt frameSize);
	Vector2DInt GetSize();
	unsigned int GetPixel(Vector2DInt pos);
private:
	Texture(const std::filesystem::path& filePath);
	Texture(doodle::Image&& doodleImage);
	doodle::Image image;
};
