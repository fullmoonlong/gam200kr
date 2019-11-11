/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "PATH.hpp"
#include "Application.h"
#include "VerticesDescription.h"
#include "Image.hpp"

Application::Application()
{
	Initialize();
	isRunning = true;
}

void Application::Initialize()
{
	window.CanCreateWindow(800, 600, this,"Lasik"); //initialize window

	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);
	shader2.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);
	//shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	//shader2.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	//shader.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
	//shader2.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
	
	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	const Color4f color2{ 0.5f, 0.5f, 0.3f, 1.0f };
	const float starting_x = 300.0f;
	const float starting_y = 0.0f;
	const float width = 50.0f;
	const float height = 50.0f;
	rectangle = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
	rectangle2 = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color2);
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	vertices2.InitializeWithMeshAndLayout(rectangle2, layout);

	material.vertices = vertices;
	material.mesh = rectangle;
	material2.vertices = vertices2;
	material2.mesh = rectangle2;
	
	Image image(PATH::kevin_move);
	Image image2(PATH::kevin_attack);

	animation.Initialize(image2, rectangle, 7, shader);
	animation2.Initialize(image2, rectangle2, 7, shader);
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera

	//dynamic test
	objectTest = new Object();
	objectTest->Initialize({ -300.0f, 0.0f }, width, height);
	objectTest->SetType(UnitType::Player);
	objectTest->speed.x = 150.0f;
	objectTest->image.LoadFrom(PATH::kevin_attack);

	const Color4f color3{ 1.0f, 0.0f, 0.0f, 1.0f };

	objectTest->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color3);
	objectTest->vertices.InitializeWithMeshAndLayout(objectTest->mesh, layout);

	objectTest->material.vertices = objectTest->vertices;
	objectTest->material.mesh = objectTest->mesh;

	objectTest->animation.Initialize(objectTest->image, objectTest->mesh, 7, shader);

	//object2
	objectTest1 = new Object();
	objectTest1->Initialize({ starting_x, starting_y }, width, height);
	objectTest->SetType(UnitType::Enemy);
	objectTest1->speed.x -= 150.0f;
	objectTest1->image.LoadFrom(PATH::kevin_attack);

	const Color4f color4{ 1.0f, 0.0f, 0.0f, 1.0f };

	objectTest1->mesh = MESH::create_rectangle(0.f, 0.f, -1.0f, 1.0f, color4);
	objectTest1->vertices.InitializeWithMeshAndLayout(objectTest1->mesh, layout);

	objectTest1->material.vertices = objectTest1->vertices;
	objectTest1->material.mesh = objectTest1->mesh;

	objectTest1->animation.Initialize(objectTest1->image, objectTest1->mesh, 7, shader);
	//dynamic test

	object.Initialize({ starting_x, starting_y }, width, height);
	object.speed.x = -150.0f;
	object2.Initialize({-300.0f, 0.0f }, width, height);
	object2.speed.x = 150.0f;
}

void Application::Update()
{
	clock.UpdateClock();

	OBJECTFACTORY->Update();

	//Object moving
	object.Update(deltaTime);
	object2.Update(deltaTime);
	
	//if (object.GetXposition() < 0.0f)
	//{
	//	animation.ChangeAnimation(PATH::kevin_attack, 7);
	//	object.speed.x = 0.0f;
	//}
	//Object moving


	//Draw
	draw.StartDrawing();

	//draw.draw(shader, material);
	//animation.Animate(deltaTime);
	//const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object.transform.GetModelToWorld();
	//shader.SendUniformVariable("ndc", ndc);

	//draw.draw(shader, material2);
	//animation2.Animate(deltaTime);
	//const mat3<float> ndc2 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object2.transform.GetModelToWorld();
	//shader.SendUniformVariable("ndc", ndc2);

	//dynamic test
	for (auto obj : OBJECTFACTORY->GetObjecteList())
	{
		if (obj.second != nullptr)
		{
			obj.second->Update(deltaTime);
			obj.second->animation.Animate(deltaTime);
			draw.draw(shader, obj.second->material);
			const mat3<float> ndc3 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->transform.GetModelToWorld();
			shader.SendUniformVariable("ndc", ndc3);
		}
	}
	//dynamic test

	draw.Finish();
	//Draw

	
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//Transform

	++frameCount;
	static int time = 0;
	if (clock.timePassed >= 1.0f)
	{
		++time;
		std::cout << time << std::endl;
		std::cout << frameCount << std::endl;
		clock.timePassed -= 1.0f;
		frameCount = 0;
	}
	deltaTime = clock.GetTimeFromLastUpdate();
	
	window.SwapBuffers();
	window.PollEvents();
}

void Application::ShutDown()
{
	isRunning = false;
	glfwSetWindowShouldClose(window.window, GLFW_TRUE);
}

void Application::HandleKeyPress(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Escape:
		this->ShutDown();
		break;
	case KeyboardButtons::F:
		window.ToggleFullScreen();
		break;
	case KeyboardButtons::V:
		if (window.IsVSyncOn() == false)
		{
			window.ToggleVSync(true);
			break;
		}
		window.ToggleVSync(false);
		break;
	case KeyboardButtons::W:
		//pressDirection.y += 
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? -2.0f : 2.0f;
		//object.speed.y = 0.8f;
		break;
	case KeyboardButtons::S:
		//pressDirection.y +=
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 2.0f : -2.0f;
		//object.speed.y = -0.8f;
		OBJECTFACTORY->DestroyAllObjects();
		break;
	case KeyboardButtons::A:
		//pressDirection.x -= 2.0f;
		OBJECTFACTORY->CopyObject(objectTest);
		//object.speed.x = -0.8f;
		break;
	case KeyboardButtons::D:
		//pressDirection.x += 2.0f;
		OBJECTFACTORY->CopyObject(objectTest1);
		//object.speed.x = 0.8f;
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
		//object.speed.y = 0.f;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		//object.speed.y = 0.f;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		//object.speed.x = 0.f;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		//object.speed.x = 0.f;
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
		if (object.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
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
	window.SetWindowWidth(width);
	window.SetWindowHeight(height);
	glfwSetWindowSize(window.window, width, height);
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
