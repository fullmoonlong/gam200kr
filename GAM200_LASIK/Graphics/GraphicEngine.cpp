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
#include <Graphics/Image.hpp>
#include "GraphicEngine.h"


const std::filesystem::path vertex_path = "../assets/texture.vert";
const std::filesystem::path fragment_path = "../assets/texture.frag";

const std::filesystem::path vertex_test = "../assets/shape.vert";
const std::filesystem::path fragmenet_test = "../assets/shape.frag";

const std::filesystem::path texture_image = "../assets/sprite.png";

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

GraphicEngine::GraphicEngine()
{
	Initialize();
	isRunning = true;
}

void GraphicEngine::Initialize()
{
	glWindow.CanCreateWindow(800, 600, this,"Prototype"); //initialize window

	const std::string vertex_source = ReadSourceFrom(vertex_test);
	const std::string fragment_source = ReadSourceFrom(fragmenet_test);

	shader.LoadShader(vertex_source, fragment_source);

	Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	rectangle = MESH::draw_rectangle(50.f, 50.f, 150.f, 50.f, color);

	ShaderDescription layout{ ShaderDescription::Type::Point, ShaderDescription::Type::Color };
	shader.InitializeWithMesh(rectangle, layout);

	//camera
	view.SetViewSize(glWindow.GetWindowWidth(), glWindow.GetWindowHeight());
	view.SetZoom(zoom);
	//camera

	//object1.Initialize({ 0.f,0.f }, 8);
	//object2.Initialize({ 200.f,0.f }, 8);
	//object1.min = { -50.f, -50.f };
	//object1.max = { 50.f, 50.f };
	//object2.min = { 150.f, -50.f };
	//object2.max = { 250.f, 50.f };
}

void GraphicEngine::Update()
{
	auto start = std::chrono::system_clock::now();

	static float frameTime = 0;

	glWindow.SwapBuffers();
	glWindow.PollEvents();


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader.GetHandleToShader());
	glBindVertexArray(shader.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, shader.VBO);
	mat3<float> ndc1 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object1.transform.GetModelToWorld();
	shader.SendUniformVariable("ndc", ndc1);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//if (object1.isMouseCollide == true)
	//{
	//	vec2<float> newPosition{ -((glWindow.GetWindowWidth() / 2.0f) - mousePosition.x) , -((glWindow.GetWindowHeight() / 2.0f) - mousePosition.y) };
	//	vec2<float> newPosition1{ -((glWindow.GetWindowWidth() / 2.0f) - mousePosition.x) , ((glWindow.GetWindowHeight() / 2.0f) - mousePosition.y) };
	//	object1.min.x = -50.f + newPosition.x;
	//	object1.min.y = -50.f + newPosition.y;
	//	object1.max.x = 50.f + newPosition.x;
	//	object1.max.y = 50.f + newPosition.y;
	//	object1.transform.SetTranslation(newPosition1);
	//}

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
}

void GraphicEngine::ShutDown()
{
	isRunning = false;
	glfwSetWindowShouldClose(glWindow.window, GLFW_TRUE);
}

void GraphicEngine::HandleKeyPress(KeyboardButtons button)
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
		object2.speed.y = 0.8f;
		break;
	case KeyboardButtons::S:
		//pressDirection.y +=
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 2.0f : -2.0f;
		object2.speed.y = -0.8f;
		break;
	case KeyboardButtons::A:
		//pressDirection.x -= 2.0f;
		object2.speed.x = -0.8f;
		break;
	case KeyboardButtons::D:
		//pressDirection.x += 2.0f;
		object2.speed.x = 0.8f;
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

void GraphicEngine::HandleKeyRelease(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::W:
		pressDirection.y = 0;
		object2.speed.y = 0.f;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		object2.speed.y = 0.f;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		object2.speed.x = 0.f;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		object2.speed.x = 0.f;
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

void GraphicEngine::HandleMouseEvent(MouseButtons button)
{
	switch (button)
	{
	case MouseButtons::LEFT_PRESS:
	{
		//mouse check
		if (object1.isCollideWithMouse(mousePosition, glWindow.GetWindowWidth(), glWindow.GetWindowHeight()))
		{
			object1.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButtons::LEFT_RELEASE:
		object1.isMouseCollide = false;
		break;
	}
}


void GraphicEngine::HandleResizeEvent(const int& width, const int& height)
{
	glWindow.SetWindowWidth(width);
	glWindow.SetWindowHeight(height);
	glfwSetWindowSize(glWindow.window, width, height);
	//camera
	view.SetViewSize(width, height);
	view.SetZoom(zoom);
	//camera
}

void GraphicEngine::HandleScrollEvent(float scroll_amount)
{
	zoom = view.GetZoom() + (scroll_amount * 0.05f);
	zoom = std::clamp(zoom, 0.1f, 2.0f);
	view.SetZoom(zoom);
}

void GraphicEngine::HandleMousePositionEvent(float xpos, float ypos)
{
	//vec2<float> newMousePosition{ xpos, ypos };
	mousePosition = { xpos, ypos };
}
