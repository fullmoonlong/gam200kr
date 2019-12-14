/**************************************************************************************
 *	File Name        : Draw.hpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Texture.hpp"
#include "Text.hpp"
#include "Material.hpp"

class Draw
{
public:
	static void StartDrawing();
	static void StartDrawing(const Color4f& background_color);
	static void FinishDrawing();
	static void draw(const Material& material);
	static void DrawShape(const Material& material);
	static void DrawText(const Shader& shader, const mat3<float>& ndc, const Text& text);
private:
};

