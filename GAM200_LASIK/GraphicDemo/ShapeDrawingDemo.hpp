/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: ShapeDrawingDemo.h
 *	
 *	Graphic demo main file
 *	
 *	Nov.25 2019
 *******************************************************/

#pragma  once
#include "Demo.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Transform.hpp"

class ShapeDrawingDemo : public Demo
{
public:
	explicit ShapeDrawingDemo(Window& window) : Demo(window) { Initialize(); }

	void Initialize() override final;
	void Update(float dt) override final;
	void ShutDown() override final;

	void ResetCamera() override final;

	void HandleResizeEvent(const int& new_width, const int& new_height) override;
	void HandleKeyPress(KeyboardButton button) override;
	void HandleKeyRelease(KeyboardButton button) override;
	void HandleFocusEvent(int focus) override;
private:
	vec2<float> moveSpeed{ 0.f };
	float rotationSpeed = 0;
	float speedMulti = 1;
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	Shader shader;

	Mesh rectangle;
	Vertices rectangleVertices;
	Transform rectangleTransform;
	
	Mesh line;
	Vertices lineVertices;
	Transform lineTransform;

	Mesh quad;
	Vertices quadVertices;
	Transform quadTransform;

	Mesh triangle;
	Vertices triangleVertices;
	Transform triangleTransform;

	Mesh circle;
	Vertices circleVertices;
	Transform circleTransform;

	Mesh ellipse;
	Vertices ellipseVertices;
	Transform ellipseTransform;
};
