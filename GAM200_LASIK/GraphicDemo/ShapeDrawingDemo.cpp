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
#include "ShapeDrawingDemo.hpp"
#include "Draw.hpp"
#include "PATH.hpp"

void ShapeDrawingDemo::Initialize()
{
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

	view.SetViewSize(width, height);
}

void ShapeDrawingDemo::Update()
{
	camera.Rotate(rotationSpeed);
	camera.MoveRight(moveSpeed.x);
	camera.MoveUp(moveSpeed.y);
	
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

}

void ShapeDrawingDemo::ResetCamera()
{
	camera.ResetUp();
	speedMulti = 0.0f;
}

void ShapeDrawingDemo::HandleResizeEvent(const int& new_width, const int& new_height)
{	
	Demo::HandleResizeEvent(new_width, new_height);
}

void ShapeDrawingDemo::HandleKeyPress(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::Arrow_Right:
		moveSpeed.x += speedMulti;
		break;
	case KeyboardButton::Arrow_Left:
		moveSpeed.x -= speedMulti;
		break;
	case KeyboardButton::Arrow_Up:
		moveSpeed.y += speedMulti;
		break;
	case KeyboardButton::Arrow_Down:
		moveSpeed.y -= speedMulti;
		break;
	case KeyboardButton::Z:
		rotationSpeed = 0.01f * speedMulti;
		break;
	case KeyboardButton::X:
		rotationSpeed = -0.01f * speedMulti;
		break;
	case KeyboardButton::I:
		speedMulti += 0.5f;
		break;
	case KeyboardButton::O:
		speedMulti -= 0.5f;
		break;
	}
}

void ShapeDrawingDemo::HandleKeyRelease(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::Arrow_Right:
		moveSpeed.x = 0;
		break;
	case KeyboardButton::Arrow_Left:
		moveSpeed.x = 0;
		break;
	case KeyboardButton::Arrow_Up:
		moveSpeed.y = 0;
		break;
	case KeyboardButton::Arrow_Down:
		moveSpeed.y = 0;
		break;
	case KeyboardButton::Z:
		rotationSpeed = 0.0f;
		break;
	case KeyboardButton::X:
		rotationSpeed = 0.0f;
		break;
	}
}

void ShapeDrawingDemo::HandleFocusEvent(int focus)
{
	if (focus != GLFW_TRUE)
	{
		Draw::StartDrawing();
		Draw::FinishDrawing();
	}
}
