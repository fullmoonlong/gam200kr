#include <GL\glew.h>
#include "Shader.h"
#include <iostream>

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

unsigned Shader::GetHandleToShader()
{
	return handleToShader;
}
