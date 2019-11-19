
#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Texture.hpp"
#include "Mesh.h"

struct Material
{
	Vertices vertices;
	Texture texture;
	Mesh mesh;
};

class Draw
{
public:
	
	void StartDrawing();
	void Finish();
	static void draw(const Shader& shader, const Material& material);
private:
};

