/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Draw.cpp
 *	
 *	Draw
 *	
 *	2019/11/02
 */

#include <GL/glew.h>
#include "Draw.hpp"

void Draw::StartDrawing()
{
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Draw::Finish()
{
	glFinish();
}

void Draw::draw(const Shader& shader, const Material& material)
{	
	glBindTexture(GL_TEXTURE_2D, material.texture.GetTexturehandle());
	Shader::UseShader(shader);
	Vertices::SelectVAO(material.vertices);
	glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
}
