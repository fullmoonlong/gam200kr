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
#include "Mesh.h"

const std::filesystem::path vertex_path = "../assets/test.vert";
const std::filesystem::path fragment_path = "../assets/test.frag";

Mesh circle;
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

	const Color circleColor{ 1.0f, 0.0f, 0.0f, 1.0f };
	
	circle = MESH::draw_ellipse(0.5f, 0.5f, 30, circleColor);

	ShaderDescription circleLayout = { ShaderDescription::Type::Point };
	shader.InitializeWithMesh(circle, circleLayout);

	
	//glGenVertexArrays(1, &shader.VAO);
	//glGenBuffers(1, &shader.VBO);
	//glBindVertexArray(shader.VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, shader.VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindVertexArray(0);

}

void Application::Update()
{
	glWindow.SwapBuffers();
	glWindow.PollEvents();

	//shader.SendUniformVariable("width", (float)glWindow.GetWindowWidth());
	//shader.SendUniformVariable("height", (float)glWindow.GetWindowHeight());

	float width = (float)glWindow.GetWindowWidth();
	float height = (float)glWindow.GetWindowHeight();

	Math::mat3<float> ndc(
		2.0f / width, 0.0f, 0.0f,
		0.0f, 2.0f / height, 0.0f,
		0.0f, 0.0f, 1.0f);

	shader.SendUniformVariable("NDC", ndc);
	
	//start drawing

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(shader.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, shader.VBO);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)circle.GetPointsCount());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	//finish drawing

	
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
		this->ShutDown();
		break;
	case KeyboardButtons::F:
		glWindow.ToggleFullScreen();
		break;
	case KeyboardButtons::V:
		glWindow.ToggleVSync(true);
		break;
	case KeyboardButtons::G:
		std::cout << "G pressed" << std::endl;
	default:
		break;
	}
}

void Application::HandleKeyRelease(KeyboardButtons /*button*/)
{
	
}

void Application::HandleResizeEvent(const int& width, const int& height)
{
	glWindow.SetWindowWidth(width);
	glWindow.SetWindowHeight(height);
	glfwSetWindowSize(glWindow.window, width, height);
}

