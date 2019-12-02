/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Draw.hpp
*	
*	Draw
*	
*	2019/11/02
*/

#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Texture.hpp"
#include "Text.hpp"

struct Material
{
	Vertices vertices;
	Texture texture;
};

class Draw
{
public:
	static void StartDrawing();
	static void FinishDrawing();
	static void draw(const Shader& shader, const Material& material);
	static void DrawShape(const Shader& shader, const Vertices& vertices);
	static void DrawText(const Shader& shader, const Text& text);
private:
};

