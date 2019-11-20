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
#include "GetInput.hpp"

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
	
	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	const Color4f color2{ 0.5f, 0.5f, 0.3f, 1.0f };
	const float starting_x = 300.0f;
	const float starting_y = 0.0f;
	const float width = 50.0f;
	const float height = 50.0f;

	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera

	//dynamic test
	object1 = new Object();
	object1->Initialize({ -300.0f, 0.0f }, width, height);
	object1->SetType(UnitType::Player);
	object1->speed.x = 150.0f;
	object1->image.LoadFrom(PATH::kevin_attack);

	const Color4f color3{ 1.0f, 0.0f, 0.0f, 1.0f };

	object1->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color3);
	object1->vertices.InitializeWithMeshAndLayout(object1->mesh, layout);

	object1->material.vertices = object1->vertices;
	object1->material.mesh = object1->mesh;

	object1->animation.Initialize(object1->image, object1->mesh, 7, shader);

	//object2
	object2 = new Object();
	object2->Initialize({ starting_x, starting_y }, width, height);
	object2->SetType(UnitType::Enemy);
	object2->speed.x -= 150.0f;
	object2->image.LoadFrom(PATH::kevin_attack);

	const Color4f color4{ 1.0f, 0.0f, 0.0f, 1.0f };

	object2->mesh = MESH::create_rectangle(0.f, 0.f, -1.0f, 1.0f, color4);
	object2->vertices.InitializeWithMeshAndLayout(object2->mesh, layout);

	object2->material.vertices = object2->vertices;
	object2->material.mesh = object2->mesh;

	object2->animation.Initialize(object2->image, object2->mesh, 7, shader);
	//dynamic test

	//test sound and make object
	SOUNDMANAGER->Initialize();
	SOUNDMANAGER->LoadFile("sound.mp3");
	SOUNDMANAGER->LoadFile("beep.wav");
	SOUNDMANAGER->LoadFile("hit.ogg");
	SOUNDMANAGER->PlaySound(1, 0);
	//test sound and make object
}

void Application::Update()
{
	clock.UpdateClock();

	OBJECTFACTORY->Update();
	if (object1->speed.x == 0.f)
	{
		object1->SetStatus(IDLE);
	}
	else if (object1->speed.x > 0.f)
	{
		object1->SetStatus(MOVE);
	}

	if (object2->speed.x == 0.f)
	{
		object2->SetStatus(IDLE);
	}
	else if (object2->speed.x > 0.f)
	{
		object2->SetStatus(MOVE);
	}

	//if (object1->GetStatus() == MOVE)
	//{
	//	std::cout << "obj1 MOVE" << std::endl;
	//}
	//if (object2->GetStatus() == MOVE)
	//{
	//	std::cout << "obj2 MOVE" << std::endl;
	//}
	//Draw
	draw.StartDrawing();

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
		input.TakeAsInput();
		if (input.MatchStringWithInput() == 1)
		{
			SOUNDMANAGER->PlaySound(0, 1);
			OBJECTFACTORY->CopyObject(object1);
		}
		//object.speed.x = -0.8f;
		break;
	case KeyboardButtons::D:
		//pressDirection.x += 2.0f;
		SOUNDMANAGER->PlaySound(0, 1);
		OBJECTFACTORY->CopyObject(object2);
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
