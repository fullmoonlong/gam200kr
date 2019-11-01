/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "Application.h"
<<<<<<< Updated upstream
#include <Graphics/Image.hpp>


const std::filesystem::path vertex_path = "../assets/texture.vert";
const std::filesystem::path fragment_path = "../assets/texture.frag";

const std::filesystem::path vertex_test = "../assets/shape.vert";
const std::filesystem::path fragmenet_test = "../assets/shape.frag";

const std::filesystem::path texture_image = "../assets/sprite.png";

std::string ReadSourceFrom(const std::filesystem::path& path)
=======
#include <graphic/Image.hpp>
#include "graphic/VerticesDescription.h"

namespace PATH
>>>>>>> Stashed changes
{
	const std::filesystem::path prototype_vert = "../assets/prototype.vert";
	const std::filesystem::path prototype_frag = "../assets/prototype.frag";

	const std::filesystem::path texture_vert = "../assets/test.vert";
	const std::filesystem::path texture_frag = "../assets/test.frag";
	
	const std::filesystem::path texture_image = "../assets/sprite.png";
}

Application::Application()
{
	Initialize();
	isRunning = true;
}

void Application::Initialize()
{
	glWindow.CanCreateWindow(800, 600, this,"Prototype"); //initialize window
	const std::string vertex_source = ReadSourceFrom(vertex_path);
	const std::string fragment_source = ReadSourceFrom(fragment_path);
	const std::string vertex_source2 = ReadSourceFrom(vertex_path2);
	const std::string fragment_source2 = ReadSourceFrom(fragment_path2);
	shader.LoadShader(vertex_source, fragment_source);
	shader2.LoadShader(vertex_source2, fragment_source2);

	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	rectangle = MESH::createRectangle(0.0f, 0.0f, 150.f, 150.f, color);
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	vertices.InitializeWithMeshAndLayout(rectangle, layout);

	
	//camera
	view.SetViewSize(glWindow.GetWindowWidth(), glWindow.GetWindowHeight());
	view.SetZoom(zoom);
	//camera

	//Image image(PATH::texture_image);
	//texture.LoadTextureFrom(image);
	texture.LoadTextureFrom(PATH::texture_image);

	object.Initialize({ 0, 0 }, 8);
	object.min = { -75.0f, -75.0f };
	object.max = { 75.0f, 75.0f };
}

void Application::Update()
{
	auto start = std::chrono::system_clock::now();
	static float frameTime = 0;

	glWindow.SwapBuffers();
	glWindow.PollEvents();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Make graphic engine extern and doing something like graphic application.
	//So that it can be use like graphicApplication.Draw()
	//Draw
	glUseProgram(shader.GetHandleToShader());
	Vertices::SelecteVAO(vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices.VBO);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexturehandle());
	glDrawArrays(vertices.GetPattern(), 0,	(int)rectangle.GetPointsCount());
	//Draw
	
	mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object.transform.GetModelToWorld();
	shader.SendUniformVariable("ndc", ndc);

	object.Update(deltaTime);
	
	// transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(glWindow.GetWindowWidth(), glWindow.GetWindowHeight());
	view.SetZoom(zoom);
	// transform

	
	auto currentTime = std::chrono::system_clock::now();
	deltaTime = std::chrono::duration<float>(currentTime - start).count();

	frameCount++;
	timePassed += deltaTime;
	static float timeCheck = 0;
	frameTime += deltaTime;
	if (timePassed >= 1.0f)
	{
		timeCheck++;
		std::cout << frameCount << std::endl;
		std::cout << timeCheck << std::endl;
		frameCount = 0;
		timePassed = 0;
	}
	
	//clock.UpdateTime();
	//std::cout << clock.GetTimeBySecond() << std::endl;
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
		if (glWindow.IsVSyncOn() == false)
		{
			glWindow.ToggleVSync(true);
			break;
		}
		glWindow.ToggleVSync(false);
		break;
	case KeyboardButtons::W:
		//pressDirection.y += 
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? -2.0f : 2.0f;
		object.speed.y = 0.8f;
		break;
	case KeyboardButtons::S:
		//pressDirection.y +=
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 2.0f : -2.0f;
		object.speed.y = -0.8f;
		break;
	case KeyboardButtons::A:
		//pressDirection.x -= 2.0f;
		object.speed.x = -0.8f;
		break;
	case KeyboardButtons::D:
		//pressDirection.x += 2.0f;
		object.speed.x = 0.8f;
		break;
	case KeyboardButtons::Z:
		cameraAngle += 0.025f;
		break;
	case KeyboardButtons::X:
		cameraAngle -= 0.025f;
		break;
	default:;
	}
}

void Application::HandleKeyRelease(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::W:
		pressDirection.y = 0;
		object.speed.y = 0.f;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		object.speed.y = 0.f;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		object.speed.x = 0.f;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		object.speed.x = 0.f;
		break;
	case KeyboardButtons::Z:
		cameraAngle = 0.0f;
		break;
	case KeyboardButtons::X:
		cameraAngle = 0.0f;
		break;
	default:;
	}
}

void Application::HandleMouseEvent(MouseButtons button)
{
	switch (button)
	{
	case MouseButtons::LEFT_PRESS:
	{
		//mouse check
		if (object.isCollideWithMouse(mousePosition, glWindow.GetWindowWidth(), glWindow.GetWindowHeight()))
		{
			object.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButtons::LEFT_RELEASE:
		object.isMouseCollide = false;
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

void Application::HandleMousePositionEvent(float xpos, float ypos)
{
	//vec2<float> newMousePosition{ xpos, ypos };
	mousePosition = { xpos, ypos };
}
