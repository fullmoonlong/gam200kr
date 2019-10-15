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
#include "Image.hpp"

const std::filesystem::path vertex_path = "../assets/test.vert";
const std::filesystem::path fragment_path = "../assets/test.frag";

const std::filesystem::path texture_image = "../assets/wall.png";

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

unsigned int VAO;
unsigned int VBO;

float vertices[] = {
	// positions		// colors			// texCoords
	-200.f, -200.f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	200.f, -200.f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	200.f,  200.f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
	-200.f, 200.f,		0.7f, 0.7f, 0.7f,	0.0f, 1.0f
};

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, this, "Prototype"); //initialize window
	const std::string vertex_source = ReadSourceFrom(vertex_path);
	const std::string fragment_source = ReadSourceFrom(fragment_path);
	shader.LoadShader(vertex_source, fragment_source);


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Image image;
	image.LoadFrom(texture_image);
	texture.LoadTextureFrom(image);

	//camera
	view.SetViewSize(glWindow.GetWindowWidth(), glWindow.GetWindowHeight());
	view.SetZoom(zoom);
	//camera
}

void Application::Update()
{
	glWindow.SwapBuffers();
	glWindow.PollEvents();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);



	glUseProgram(shader.GetHandleToShader());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexturehandle());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	level.Update();


	//camera
	camera.MoveRight(pressDirection.x);
	camera.MoveUp(pressDirection.y);
	camera.Rotate(cameraAngle);

	transform.SetTranslation(pressDirection);
	transform.SetRotation(cameraAngle);

	glm::mat3 ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	shader.SendUniformVariable("ndc", ndc);

	view.SetViewSize(glWindow.GetWindowWidth(), glWindow.GetWindowHeight());
	view.SetZoom(zoom);
	//camera
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
		//view.SetFrameOfReference(FrameOfReference((view.GetFrameOfReference() + 1) % 3));
		break;
	case KeyboardButtons::W:
		pressDirection.y +=
			(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? -1.0f : 1.0f;
		break;
	case KeyboardButtons::S:
		pressDirection.y +=
			(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 1.0f : -1.0f;
		break;
	case KeyboardButtons::A:
		pressDirection.x -= 1.0f;
		break;
	case KeyboardButtons::D:
		pressDirection.x += 1.0f;
		break;
	case KeyboardButtons::Z:
		cameraAngle += 0.005f;
		break;
	case KeyboardButtons::X:
		cameraAngle -= 0.005f;
		break;
	default:
		break;
	}
}

void Application::HandleKeyRelease(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::W:
		pressDirection.y = 0;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		break;
	case KeyboardButtons::Z:
		cameraAngle = 0.0f;
		break;
	case KeyboardButtons::X:
		cameraAngle = 0.0f;
		break;
	}
}

void Application::HandleResizeEvent(const int& width, const int& height)
{
	glWindow.SetWindowWidth(width);
	glWindow.SetWindowHeight(height);
	glfwSetWindowSize(glWindow.window, width, height);
	//camera
	view.SetViewSize(width, height);
	view.SetZoom(zoom);
	//camera
}

void Application::HandleScrollEvent(float scroll_amount)
{
	zoom = view.GetZoom() + (scroll_amount * 0.05f);
	zoom = std::clamp(zoom, 0.1f, 2.0f);
	view.SetZoom(zoom);
}
