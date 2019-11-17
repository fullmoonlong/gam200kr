
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
	Vertices::SelectVAO(material.vertices);
	Shader::UseShader(shader);
	//glBindBuffer(GL_ARRAY_BUFFER, material.vertices.VBO);
	glDrawArrays(material.vertices.GetPattern(), 0, (int)material.mesh.GetPointsCount());
}
