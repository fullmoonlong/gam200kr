/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: ShapeDrawingDemo.cpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.25 2019
 *******************************************************/

#include "ShapeDrawingDemo.hpp"
#include "Draw.hpp"
#include "PATH.hpp"

void ShapeDrawingDemo::Initialize()
{
	shader.LoadShaderFrom(PATH::shape_vert, PATH::shape_frag);
	const Color4f color{ .8f, .8f, .0f, 1.0f };

	vec2<float> size{ 50.0f };
	rectangle = MESH::create_rectangle({ 0.0f }, size, color);
	rectangleVertices.InitializeWithMeshAndLayout(rectangle, layout);

	line = MESH::create_line({ 100.0f, 0.0f }, { 50.0f, 50.0f }, { -50.0f, -50.0f }, color);
	lineVertices.InitializeWithMeshAndLayout(line, layout);

	quad = MESH::create_quad({ 0.0f, 100.0f }, { -20.f, 25.f }, { -50.f, -25.f }, { 50.f, -25.f }, { 20.f, 25.f }, color);
	quadVertices.InitializeWithMeshAndLayout(quad, layout);

	triangle = MESH::create_triangle({ 100.0f }, { 0.0f, 50.0f }, { -30.f, 0.0f }, { 30.f, 0.0f }, color);
	triangleVertices.InitializeWithMeshAndLayout(triangle, layout);

	circle = MESH::create_ellipse({ 200.0f, 25.0f }, { 25.0f, 25.0f }, 30, color);
	circleVertices.InitializeWithMeshAndLayout(circle, layout);

	ellipse = MESH::create_ellipse({ -200.0f, 25.0f }, { 25.0f, 15.f }, 30, color);
	ellipseVertices.InitializeWithMeshAndLayout(ellipse, layout);

	view.SetViewSize(width, height);
}

void ShapeDrawingDemo::Update(float /*dt*/)
{
	camera.Rotate(rotationSpeed);
	camera.MoveRight(moveSpeed.x);
	camera.MoveUp(moveSpeed.y);
	
	Draw::StartDrawing();
	
	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * rectangleTransform.GetModelToWorld();
	const mat3<float> lineNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * lineTransform.GetModelToWorld();
	const mat3<float> quadNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * quadTransform.GetModelToWorld();
	const mat3<float> ellipseNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * ellipseTransform.GetModelToWorld();
	const mat3<float> triangleNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * triangleTransform.GetModelToWorld();
	const mat3<float> circleNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * circleTransform.GetModelToWorld();

	shader.SendUniformVariable("ndc", ndc);
	Draw::DrawShape(shader, rectangleVertices);

	shader.SendUniformVariable("ndc", lineNDC);
	Draw::DrawShape(shader, lineVertices);

	shader.SendUniformVariable("ndc", quadNDC);
	Draw::DrawShape(shader, quadVertices);

	shader.SendUniformVariable("ndc", triangleNDC);
	Draw::DrawShape(shader, triangleVertices);

	shader.SendUniformVariable("ndc", circleNDC);
	Draw::DrawShape(shader, circleVertices);

	shader.SendUniformVariable("ndc", ellipseNDC);
	Draw::DrawShape(shader, ellipseVertices);
	
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
