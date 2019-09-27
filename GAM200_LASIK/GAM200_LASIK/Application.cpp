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
#include <iostream>
#include <filesystem>

const std::filesystem::path vertex_path = "assets\\test.vert";
const std::filesystem::path fragment_path = "assets\\test.frag";

Object* test;

Application::Application()
{
}

Application::~Application()
{
}

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, "Prototype"); //initialize window
	shader.LoadShader(vertex_path.filename().generic_string(), fragment_path.filename().generic_string());

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
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

		glUseProgram(shader.GetHandleToShader());
		glBindVertexArray(shader.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//finish drawing

		std::cout << test->GetXpos() << " " << test->GetYpos() << std::endl;
		test->SetXpos(static_cast<int>(1));
		test->SetYpos(static_cast<int>(1));

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


