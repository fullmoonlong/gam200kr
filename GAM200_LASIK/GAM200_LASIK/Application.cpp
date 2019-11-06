/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include "Graphics/PATH.hpp"
#include "Application.h"
#include "Graphics/Image.hpp"
#include "Graphics/VerticesDescription.h"

Application::Application()
{
	Initialize();
	isRunning = true;
}

unsigned int vbo;

void Application::Initialize()
{
	Window.CanCreateWindow(800, 600, this,"Lasik"); //initialize window

	//shader.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	
	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	const float starting_x = 0.0f;
	const float starting_y = 0.0f;
	const float width = 150.0f;
	const float height = 150.0f;
	rectangle = MESH::create_rectangle(starting_x, starting_y, width, height, color);
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	vertices.InitializeWithMeshAndLayout(rectangle, layout);


	
	glGenBuffers(1, &vbo);
	Image image(PATH::sprite_image);
	
	animation.Initialize(image, rectangle, 8);


	
	//camera
	view.SetViewSize(Window.GetWindowWidth(), Window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera
	
	object.Initialize({ starting_x, starting_y }, width, height);
}

void Application::Update()
{
	clock.UpdateClock();

	Window.SwapBuffers();
	Window.PollEvents();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Make graphic engine extern and doing something like graphic application.
	//So that it can be use like graphicApplication.Draw()
	//Draw
	glUseProgram(shader.GetHandleToShader());
	Vertices::SelecteVAO(vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vertices.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	animation.Animate(deltaTime);
	glDrawArrays(vertices.GetPattern(), 0, (int)rectangle.GetPointsCount());
	//Animation
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	//Draw

	//Object moving
	object.Update(deltaTime);
	if (-400.0f < object.GetXposition() && object.GetXposition() < -300.0f)	//if collide
	{
		std::cout << "fight!" << std::endl;
		object.speed.x = 0.0f;
	}
	else
	{
		object.speed.x = -50.0f;
	}
	//Object moving

	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object.transform.GetModelToWorld();
	shader.SendUniformVariable("ndc", ndc);

	
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(Window.GetWindowWidth(), Window.GetWindowHeight());
	view.SetZoom(zoom);
	//Transform

	++frameCount;
	if (clock.timePassed >= 1.0f)
	{
		std::cout << frameCount << std::endl;
		clock.timePassed -= 1.0f;
		frameCount = 0;
	}
	deltaTime = clock.GetTimeFromLastUpdate();
}

void Application::ShutDown()
{
	isRunning = false;
	glfwSetWindowShouldClose(Window.window, GLFW_TRUE);
}

void Application::HandleKeyPress(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Escape:
		this->ShutDown();
		break;
	case KeyboardButtons::F:
		Window.ToggleFullScreen();
		break;
	case KeyboardButtons::V:
		if (Window.IsVSyncOn() == false)
		{
			Window.ToggleVSync(true);
			break;
		}
		Window.ToggleVSync(false);
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
		if (object.isCollideWithMouse(mousePosition, Window.GetWindowWidth(), Window.GetWindowHeight()))
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
	Window.SetWindowWidth(width);
	Window.SetWindowHeight(height);
	glfwSetWindowSize(Window.window, width, height);
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
