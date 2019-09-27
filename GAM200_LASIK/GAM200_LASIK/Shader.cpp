#include <GL\glew.h>
#include "Shader.h"

Shader::Shader(const std::string& vertex_source, const std::string& fragment_source) noexcept
{
	LoadShader(vertex_source, fragment_source);
}

bool Shader::LoadShader(const std::string& vertex_source,
	const std::string& fragment_source) noexcept
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
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
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
