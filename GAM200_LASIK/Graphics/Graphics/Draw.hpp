/**************************************************************************************
 *	File Name        : Draw.hpp
 *	Project Name     : Keyboard Warriors
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
	static void draw(Material& material);
	static void DrawShape(Material& material);
	static void DrawText(const Shader& shader, const mat3<float>& ndc, const Text& text);
};

class Object;
class Renderer {
public:
	Renderer() noexcept;
	
	void Draw(Object* object);
	void Draw(const mat3<float>& ndc, const Text& text);
private:
	Shader shapeShader;
	Shader spriteShader;
	Shader animationShader;
	Shader textShader;
	//Shader particleShader;
};

