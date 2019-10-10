/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Shader.cpp
*	
*	Implementing shader
*	
*	2019/09/25
*/

#include <GL\glew.h>
#include <iostream>
#include <vec2.hpp>
#include "Shader.h"
#include "Mesh.h"

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source) noexcept
{
	VAO = 0;
	VBO = 0;
	LoadShader(vertex_source, fragment_source);
}

bool Shader::LoadShader(const std::string& vertex_source, const std::string& fragment_source) noexcept
{
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexSource = vertex_source.c_str();
	const char* fragmentSource = fragment_source.c_str();

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint isVertexCompiled;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isVertexCompiled);
	if (isVertexCompiled != GL_TRUE)
	{
		GLsizei length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(vertexShader, 1024, &length, message);
		std::cout << "Vertex shader compile failure" << std::endl;
		std::cout << message << std::endl;
	}

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	GLint isFragmentCompiled;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isFragmentCompiled);
	if (isFragmentCompiled != GL_TRUE)
	{
		GLsizei length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(fragmentShader, 1024, &length, message);
		std::cout << "Fragment shader compile failure" << std::endl;
		std::cout << message << std::endl;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	GLint programLinked;
	glGetProgramiv(program, GL_LINK_STATUS, &programLinked);
	if (programLinked != GL_TRUE)
	{
		GLsizei length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &length, message);
	}

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (handleToShader != 0)
	{
		glDeleteProgram(handleToShader);
	}
	handleToShader = program;
	return true;
}

void Shader::InitializeWithMesh(const Mesh& mesh, const ShaderDescription& shader_layout) noexcept
{
	VAO = 0;
	VBO = 0;
	switch (mesh.GetShapePattern())
	{
	case ShapePattern::Triangle:
		pattern = GL_TRIANGLES;
		break;
	case ShapePattern::TriangleFan:
		pattern = GL_TRIANGLE_FAN;
		break;
	case ShapePattern::TriangleStrip:
		pattern = GL_TRIANGLE_STRIP;
		break;
	default:
		break;
	}
	layout = shader_layout;
	verticesCount = (int)mesh.GetPointsCount();
	bufferVertexCapacity = static_cast<int>(verticesCount * layout.GetPointsNum());
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bufferVertexCapacity, NULL, GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);
	layout.EnableAttributes();
	WriteMeshDataToVertexBuffer(mesh);
	
}

unsigned Shader::GetHandleToShader() const noexcept
{
	return handleToShader;
}

void Shader::SendUniformVariable(const char* variable_name, const int& variable) const noexcept
{
	const int location = glGetUniformLocation(handleToShader, variable_name);
	glUniform1i(location, variable);
}

void Shader::SendUniformVariable(const char* variable_name, const float& variable) const noexcept
{
	const int location = glGetUniformLocation(handleToShader, variable_name);
	glUniform1f(location, variable);
}

void Shader::SendUniformVariable(const char* variable_name, const Math::mat3<float>& matrix) const noexcept
{
	const int location = glGetUniformLocation(handleToShader, variable_name);
	float matrix3[] = {
		matrix.elements[0][0], matrix.elements[0][1], matrix.elements[0][2],
		matrix.elements[1][0], matrix.elements[1][1], matrix.elements[1][2],
		matrix.elements[2][0], matrix.elements[2][1], matrix.elements[2][2]
	};
	glUniformMatrix3fv(location, 1, false, matrix3);
}

void Shader::WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept
{
	char* buffer = reinterpret_cast<char*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	unsigned offset = 0;
	
	Math::vec2<float> point;
	Color color;
	Math::vec2<float> texture;
	
	for (int i = 0; i < static_cast<int>(verticesCount); i++)
	{
		for (ShaderDescription::Type element : layout.GetTypes())
		{
			switch (element)
			{
			case ShaderDescription::Point:
				point = mesh.GetPoint(i);
				memcpy(buffer + offset, &point, sizeof(point));
				offset += sizeof(Math::vec2<float>);
				break;
			case ShaderDescription::Color:
				color = mesh.GetColor(i);
				memcpy(buffer + offset, &color, sizeof(color));
				offset += sizeof(Color);
				break;
			case ShaderDescription::TextCoordinate:
				texture = mesh.GetTextureCoordinate(i);
				memcpy(buffer + offset, &texture, sizeof(texture));
				offset += sizeof(Math::vec2<float>);
				break;
			}
		}
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
