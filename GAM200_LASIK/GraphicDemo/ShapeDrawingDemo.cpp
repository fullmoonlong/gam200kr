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
	const Color4f lineColor{ .0f, .0f };

	rectangle = MESH::create_rectangle(.0f, .0f, 50.f, 50.f, color);
	rectangleVertices.InitializeWithMeshAndLayout(rectangle, layout);
	rectangleTransform.SetTranslation({ 150.0f, 150.0f });

	line = MESH::create_line({ 50.0f, 50.0f }, { -50.0f, -50.0f }, lineColor);
	lineVertices.InitializeWithMeshAndLayout(line, layout);
	lineTransform.SetTranslation({ 300.0f, 150.0f });

	quad = MESH::create_quad({ -20.f, 25.f }, { -50.f, -25.f }, { 50.f, -25.f }, { 20.f, 25.f }, color);
	quadVertices.InitializeWithMeshAndLayout(quad, layout);
	quadTransform.SetTranslation({ 150.f, 300.0f });

	ellipse = MESH::create_ellipse(25.0f, 25.0f, 30, color);
	ellipseVertices.InitializeWithMeshAndLayout(ellipse, layout);
	ellipseTransform.SetTranslation({ 300.0f, 300.0f });

	triangle = MESH::create_triangle({ 0.0f, 50.0f }, { -30.f, 0.0f }, { 30.f, 0.0f }, color);
	triangleVertices.InitializeWithMeshAndLayout(triangle, layout);
	triangleTransform.SetTranslation({ 150.0f, 0.0f });

	parentMesh = MESH::create_rectangle(0, 50, 50, 50, color);
	parentVertices.InitializeWithMeshAndLayout(parentMesh, layout);
	max

	childMesh = MESH::create_rectangle(0, 0, 50,50, { 0.8f, 0.f, 0.8f, 1.0f });
	childVertices.InitializeWithMeshAndLayout(childMesh, layout);
	childTransform.SetParent(&parentTransform);
	//childTransform.SetScale({ 50 });

	view.SetViewSize(width, height);
}

void ShapeDrawingDemo::Update()
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
	const mat3<float> parentNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * parentTransform.GetModelToWorld();
	const mat3<float> childNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * childTransform.GetModelToWorld();
	
	shader.SendUniformVariable("ndc", ndc);
	Draw::DrawShape(shader, rectangleVertices);

	shader.SendUniformVariable("ndc", lineNDC);
	Draw::DrawShape(shader, lineVertices);

	shader.SendUniformVariable("ndc", quadNDC);
	Draw::DrawShape(shader, quadVertices);

	shader.SendUniformVariable("ndc", ellipseNDC);
	Draw::DrawShape(shader, ellipseVertices);

	shader.SendUniformVariable("ndc", triangleNDC);
	Draw::DrawShape(shader, triangleVertices);

	shader.SendUniformVariable("ndc", parentNDC);
	Draw::DrawShape(shader, parentVertices);

	shader.SendUniformVariable("ndc", childNDC);
	Draw::DrawShape(shader, childVertices);
	
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

void ShapeDrawingDemo::HandleMousePositionEvent(float xpos, float ypos)
{
	mousePosition.x = xpos - width / 2.f;
	mousePosition.y = -ypos + height / 2.f;
}

void ShapeDrawingDemo::HandleMouseEvent(MouseButton button)
{
	vec2<float> t = childTransform.GetTranslation();
	vec2<float> s = childTransform.GetScale();
	switch (button)
	{
	case MouseButton::LEFT_PRESS:
		if (!(t.x - s.x > mousePosition.x || mousePosition.x > t.x + s.x || t.y - s.y > mousePosition.y || mousePosition.y > t.y + s.y))
		{
			isMouseCollide = true;
		}
		break;
	case MouseButton::LEFT_RELEASE:
		isMouseCollide = false;
		break;
	}
}
