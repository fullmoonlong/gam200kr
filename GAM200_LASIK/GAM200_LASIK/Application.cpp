/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*			Doyeong Yi doyoung.lee@digipen.edu
*	Application
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
	
	circle = MESH::draw_ellipse(30.5f, 30.5f, 30, circleColor);

	ShaderDescription circleLayout = { ShaderDescription::Type::Point, ShaderDescription::Type::Color };
	shader.InitializeWithMesh(circle, circleLayout);

}

void Application::Update()
{
	glWindow.SwapBuffers();
	glWindow.PollEvents();

	int width = glWindow.GetWindowWidth();
	int height = glWindow.GetWindowHeight();

	Math::mat3<float> ndc = Math::build_scaling<float>(2.0f / (float)width, 2.0f / (float)height);

	//start drawing

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(shader.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, shader.VBO);
	glUseProgram(shader.GetHandleToShader());	// Using shader ******* important *******
	shader.SendUniformVariable("NDC", ndc);
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

