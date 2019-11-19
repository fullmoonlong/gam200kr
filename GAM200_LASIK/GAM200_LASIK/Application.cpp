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
	check = MovestateType::MOVE;
}

void Application::Initialize()
{
	window.CanCreateWindow(800, 600, this,"Lasik"); 

	KnightShader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);
	SkeletonShader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);
	
	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	const Color4f color2{ 0.5f, 0.5f, 0.3f, 1.0f };
	const float starting_x = 300.0f;
	const float starting_y = 0.0f;
	const float width = 50.0f;
	const float height = 50.0f;
	
	SkeletonMesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
	KnightMesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color2);
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	SkeletonVertices.InitializeWithMeshAndLayout(SkeletonMesh, layout);
	KnightVertices.InitializeWithMeshAndLayout(KnightMesh, layout);

	SkeletonMaterial.vertices = SkeletonVertices;
	SkeletonMaterial.mesh     = SkeletonMesh;
	KnightMaterial.vertices = KnightVertices;
	KnightMaterial.mesh = KnightMesh;
	
	Image image (PATH::knight_move);
	Image image2(PATH::kevin_move);

	KnightAnimation.Initialize(image, KnightMesh, 8, KnightShader);
	SkeletonAnimation.Initialize(image2, SkeletonMesh,  8, SkeletonShader);
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	
	Knight.Initialize({ starting_x, starting_y }, width, height);
	Knight.speed.x = -100.0f;
	
	Skeleton.Initialize({-300.0f, 0.0f }, width, height);
	Skeleton.speed.x = 100.0f;
}

void Application::Update()
{
	clock.UpdateClock();

	if(Knight.isCollideWith(Skeleton) == true)
	{
		std::cout << "collision" << std::endl;
		check = MovestateType::ATTACK;
	}
	
	//Object moving
	Knight.Update(deltaTime);
	Skeleton.Update(deltaTime);
	
	if (check == MovestateType::ATTACK)
	{
		KnightAnimation.ChangeAnimation(PATH::knight_attack, 8);
		Knight.SetKnightHealth(20);
		Knight.speed.x = 0.0f;
		
		SkeletonAnimation.ChangeAnimation(PATH::kevin_attack, 7);
		Skeleton.speed.x = 0.0f;

	}

	if (Knight.GetKnightHealth() == 0)
	{
		check = MovestateType::DIE;
		std::cout << "Knight dead" << std::endl;
		std::cout << "Knight dead" << std::endl;
		std::cout << "Knight dead" << std::endl;
		std::cout << "Knight dead" << std::endl;
	}

	//Draw
	draw.StartDrawing();

	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * Knight.transform.GetModelToWorld();
	const mat3<float> ndc2 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * Skeleton.transform.GetModelToWorld();

	draw.draw(KnightShader, KnightMaterial);
	KnightAnimation.Animate(deltaTime);
	KnightShader.SendUniformVariable("ndc", ndc);

	draw.draw(SkeletonShader, SkeletonMaterial);
	SkeletonAnimation.Animate(deltaTime);
	SkeletonShader.SendUniformVariable("ndc", ndc2);
	
	draw.Finish();
	//Draw

	
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);


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
	//case KeyboardButtons::W:
	//	pressDirection.y += 
	//		(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? -2.0f : 2.0f;
	//	Knight.speed.y = 0.8f;
	//	break;
	//case KeyboardButtons::S:
	//	pressDirection.y +=
	//		(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 2.0f : -2.0f;
	//	Knight.speed.y = -0.8f;
	//	break;
	//case KeyboardButtons::A:
	//	pressDirection.x -= 2.0f;
	//	Knight.speed.x = -500.0f;
	//	break;
	//case KeyboardButtons::D:
	//	pressDirection.x += 2.0f;
	//	Knight.speed.x = 500.0f;
	//	break;
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
	/*case KeyboardButtons::W:
		pressDirection.y = 0;
		Knight.speed.y = 0.f;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		Knight.speed.y = 0.f;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		Knight.speed.x = 0.f;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		Knight.speed.x = 0.f;
		break;*/
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
		if (Knight.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
		{
			Knight.isMouseCollide = true;
		}
		//mouse check
		if (Skeleton.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
		{
			Skeleton.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButtons::LEFT_RELEASE:
		Knight.isMouseCollide = false;
		Skeleton.isMouseCollide = false;
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
	vec2<float> newMousePosition{ xpos, ypos };
	mousePosition = { xpos, ypos };
}
