/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: ShapeDrawingDemo.cpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.25 2019
 *******************************************************/

#include <iostream>
#include "ShapeDrawingDemo.h"
#include "Draw.hpp"
#include "PATH.hpp"

//ShapeDrawingDemo::ShapeDrawingDemo()
//{
//	isRunning = true;
//	Initialize();
//}

//bool ShapeDrawingDemo::IsRunning() const
//{
//	return isRunning;
//}

void ShapeDrawingDemo::Initialize()
{
	//if (!window.CanCreateWindow(width, height, this, "GrahpicDemo"))
	//{
	//	std::cout << "Failed to Create Window\n";
	//}
	shader.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
	const Color4f color{ .8f, .8f, .0f, 1.0f };
	const Color4f lineColor{ .0f, .0f };

	rectangle = MESH::create_rectangle(.0f, .0f, 50.f, 50.f, color);
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	transform.SetTranslation({ 150.0f, 0.0f });

	line = MESH::create_line({ 200.0f, 200.0f }, { 0.0f, 0.0f }, lineColor);
	lineVertices.InitializeWithMeshAndLayout(line, layout);
	lineTransform.SetTranslation({ 0.0f, 0.0f });

	quad = MESH::create_quad({ -20.f, 0.f }, { -50.f, -50.f }, { 50.f, -50.f }, { 20.f, 0.f }, color);
	quadVertices.InitializeWithMeshAndLayout(quad, layout);
	quadTransform.SetTranslation({ -100.f, 0.0f });

	ellipse = MESH::create_ellipse(50.f, 50.f, 30, color);
	ellipseVertices.InitializeWithMeshAndLayout(ellipse, layout);
	ellipseTransform.SetTranslation({ 0.0f, 100.0f });

	triangle = MESH::create_triangle({ 0.0f, 50.0f }, { -30.f, 0.0f }, { 30.f, 0.0f }, color);
	triangleVertices.InitializeWithMeshAndLayout(triangle, layout);
	triangleTransform.SetTranslation({ -100.0f, 100.0f });
	
	// camera
	view.SetViewSize(1280, 720);
	view.SetZoom(1.0f);
	// camera
}

void ShapeDrawingDemo::Update()
{
	//view.SetViewSize(1280, 720);
	
	Draw::StartDrawing();
	
	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	const mat3<float> lineNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * lineTransform.GetModelToWorld();
	const mat3<float> quadNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * quadTransform.GetModelToWorld();
	const mat3<float> ellipseNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * ellipseTransform.GetModelToWorld();
	const mat3<float> triangleNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * triangleTransform.GetModelToWorld();
	
	shader.SendUniformVariable("ndc", ndc);
	Draw::DrawShape(shader, vertices);

	shader.SendUniformVariable("ndc", lineNDC);
	Draw::DrawShape(shader, lineVertices);

	shader.SendUniformVariable("ndc", quadNDC);
	Draw::DrawShape(shader, quadVertices);

	shader.SendUniformVariable("ndc", ellipseNDC);
	Draw::DrawShape(shader, ellipseVertices);

	shader.SendUniformVariable("ndc", triangleNDC);
	Draw::DrawShape(shader, triangleVertices);
	
	Draw::FinishDrawing();
}

void ShapeDrawingDemo::ShutDown()
{
	//isRunning = false;
	//if (static_cast<bool>(glfwWindowShouldClose(window.window)) != true)
	//{
	//	glfwSetWindowShouldClose(window.window, GLFW_FALSE);
	//}
}

//void ShapeDrawingDemo::HandleKeyPress(KeyboardButtons button)
//{
//	//switch (button)
//	//{
//	//case KeyboardButtons::Escape:
//	//	this->ShutDown();
//	//	break;
//	//case KeyboardButtons::F:
//	//	window.ToggleFullScreen();
//	//	break;
//	//case KeyboardButtons::V:
//	//	window.ToggleVSync(!window.IsVSyncOn());
//	//	break;
//	//default:
//	//	break;
//	//}
//}
//
//void ShapeDrawingDemo::HandleResizeEvent(const int& new_width, const int& new_height)
//{
//	//window.SetWindowWidth(new_width);
//	//window.SetWindowHeight(new_height);
//
//	//camera
//	//view.SetViewSize(new_width, new_height);
//	//view.SetZoom(view.GetZoom());
//	//camera
//}
//
//void ShapeDrawingDemo::HandleScrollEvent(float scroll_amount)
//{
//	const float zoomSpeed = .05f;
//	//float newZoom = view.GetZoom() + (scroll_amount * zoomSpeed);
//	//newZoom = std::clamp(newZoom, 0.5f, 2.0f);
//	//view.SetZoom(newZoom);
//}
//
//void ShapeDrawingDemo::HandleWindowClose()
//{
//	ShutDown();
//}
