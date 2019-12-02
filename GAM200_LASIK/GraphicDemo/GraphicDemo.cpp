/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Application.cpp
 *	
 *	Graphic demo main file
 *	
 *	2019/11/25
 *******************************************************/

#include <iostream>
#include "GraphicDemo.h"
#include "Draw.hpp"
#include "PATH.hpp"

GraphicDemo::GraphicDemo()
{
	running = true;
	Initialize();
}

bool GraphicDemo::isRunning()
{
	return running;
}

void GraphicDemo::Initialize()
{
	if (!window.CanCreateWindow(width, height, this, "GrahpicDemo"))
	{
		std::cout << "Failed to Create Window\n";
	}
	shader.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
	const Color4f color{ .8f, .8f, .0f, 1.0f };
	const Color4f lineColor{ .0f, .0f };

	rectangle = MESH::create_rectangle(.0f, .0f, 50.f, 50.f, color);
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	transform.SetTranslation({ 300.0, 150.0f });

	line = MESH::create_line({ 0.0f, 0.0f }, { -200.0f, -200.0f }, lineColor);
	lineVertices.InitializeWithMeshAndLayout(line, layout);
	lineTransform.SetTranslation({ -50.0f, 0.0f });

	// camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(1.0f);
	// camera
}

void GraphicDemo::Update()
{
	Draw::StartDrawing();

	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	const mat3<float> lineNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * lineTransform.GetModelToWorld();
	Draw::DrawShape(shader, vertices);
	shader.SendUniformVariable("ndc", ndc);

	Draw::DrawShape(shader, lineVertices);
	shader.SendUniformVariable("ndc", lineNDC);
	
	Draw::FinishDrawing();
	
	window.SwapBuffers();
	window.PollEvents();
}

void GraphicDemo::ShutDown()
{
	running = false;
	if ((bool)glfwWindowShouldClose(window.window) != true)
	{
		glfwSetWindowShouldClose(window.window, GLFW_FALSE);
	}
}

void GraphicDemo::HandleKeyPress(KeyboardButtons button)
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
		window.ToggleVSync(!window.IsVSyncOn());
		break;
	}
}

void GraphicDemo::HandleResizeEvent(const int& new_width, const int& new_height)
{
	window.SetWindowWidth(new_width);
	window.SetWindowHeight(new_height);

	//camera
	view.SetViewSize(new_width, new_height);
	view.SetZoom(view.GetZoom());
	//camera
}

void GraphicDemo::HandleScrollEvent(float scroll_amount)
{
	const float zoomSpeed = .05f;
	float newZoom = view.GetZoom() + (scroll_amount * zoomSpeed);
	newZoom = std::clamp(newZoom, 0.1f, 2.0f);
	view.SetZoom(newZoom);
}

void GraphicDemo::HandleWindowClose()
{
	ShutDown();
}
