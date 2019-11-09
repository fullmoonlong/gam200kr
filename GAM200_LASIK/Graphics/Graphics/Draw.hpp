
#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Mesh.h"

struct Material
{
	Vertices vertices;
	Mesh mesh;
};

class Draw
{
public:
	
	void StartDrawing();
	void Finish();
	void draw(const Shader& shader, const Material& material);
private:
};

