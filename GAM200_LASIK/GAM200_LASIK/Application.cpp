/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/07/04
*/

#include <GL/glew.h>
#include "Object.h"
#include "Engine.h"
#include "Application.h"
#include "StateManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

const std::filesystem::path vertex_path = "../assets/test.vert";
const std::filesystem::path fragment_path = "../assets/test.frag";

std::string get_file_contents(const std::filesystem::path& path)
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

Object* test;

Application::Application()
{
	std::cout << "Application Add Successful" << std::endl;
}

Application::~Application()
{
}

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, "Prototype"); //initialize window
	const std::string vertex_source = get_file_contents(vertex_path);
	const std::string fragment_source = get_file_contents(fragment_path);
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


	test = new Object();
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

	if (glfwGetKey(glWindow.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		gameEngine->Shutdown();
	}
	else if (glfwGetKey(glWindow.window, GLFW_KEY_V) == GLFW_PRESS)
	{
		glWindow.ToggleOnVSync(!glWindow.IsVSyncOn());
	}
	else if (glfwGetKey(glWindow.window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glWindow.ToggleFullScreen(glWindow.window);
	}
}


