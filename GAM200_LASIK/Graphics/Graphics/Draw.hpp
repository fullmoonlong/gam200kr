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
#include "Mesh.h"

struct Material
{
	Vertices vertices;
	Texture texture;
};

class Draw
{
public:
	void StartDrawing();
	void Finish();
	static void draw(const Shader& shader, const Material& material);
private:
};

