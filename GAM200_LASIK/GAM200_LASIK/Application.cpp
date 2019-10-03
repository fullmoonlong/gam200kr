/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/07/04
*/

#include <GL/glew.h>
#include "Application.h"
#include <filesystem>
#include <fstream>
#include <iostream>

const std::filesystem::path vertex_path = "../assets/test.vert";
const std::filesystem::path fragment_path = "../assets/test.frag";

std::string ReadSourceFrom(const std::filesystem::path& path)
{
	std::ifstream in(path, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(unsigned(in.tellg()));
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	return {};
}

Application::Application()
{
	Initialize();
	isRunning = true;
}

Application::~Application()
{
	
}

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, this,"Prototype"); //initialize window
	const std::string vertex_source = ReadSourceFrom(vertex_path);
	const std::string fragment_source = ReadSourceFrom(fragment_path);
	shader.LoadShader(vertex_source, fragment_source);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		0.5f, -0.5f, 0.0f, // right
		0.0f,  0.5f, 0.0f  // top
	}; 

	glGenVertexArrays(1, &shader.VAO);
	glGenBuffers(1, &shader.VBO);
	glBindVertexArray(shader.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, shader.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void Application::Update()
{
	glWindow.SwapBuffers();
	glWindow.PollEvents();
	
	//start drawing

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader.GetHandleToShader());
	glBindVertexArray(shader.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//finish drawing

	//std::cout << test->GetXpos() << " " << test->GetYpos() << std::endl;
	//test->SetXpos(static_cast<int>(1));
	//test->SetYpos(static_cast<int>(1));

	
}

void Application::ShutDown()
{
	isRunning = false;
	glfwSetWindowShouldClose(glWindow.window, GLFW_TRUE);
}

void Application::HandleKeyPress(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Escape:
		std::cout << "ESC pressing" << std::endl;
		break;
	default:
		break;
	}
}

void Application::HandleKeyTriggered(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Escape:
		std::cout << "ESC triggered" << std::endl;
		break;
	case KeyboardButtons::F:
		glWindow.ToggleFullScreen();
		break;
	case KeyboardButtons::V:
		glWindow.ToggleVSync(true);
		break;
	}
}

void Application::HandleKeyRelease(KeyboardButtons /*button*/)
{
}
