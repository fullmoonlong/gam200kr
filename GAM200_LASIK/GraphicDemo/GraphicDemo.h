/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Application.h
 *	
 *	Graphic demo main file
 *	
 *	2019/11/25
 *******************************************************/

#pragma  once
#include "OpenGL_Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Texture.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Transform.hpp"
#include "EventHandler.hpp"

class GraphicDemo : public SimpleEventHandler
{
public:
	GraphicDemo();
	bool IsRunning() const;
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override final;
	void HandleWindowClose() override final;
	void HandleResizeEvent(const int& width, const int& height) override final;
	void HandleScrollEvent(float scroll_amount) override final;
private:
	bool isRunning;
	Window window;
	const int width = 1280;
	const int height = 720;
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
	Shader shader;

	Camera camera;
	CameraView view;
	
	Mesh rectangle;
	Vertices vertices;
	Transform transform;
	
	Mesh line;
	Vertices lineVertices;
	Transform lineTransform;

	Mesh quad;
	Vertices quadVertices;
	Transform quadTransform;

	Mesh ellipse;
	Vertices ellipseVertices;
	Transform ellipseTransform;

	Mesh triangle;
	Vertices triangleVertices;
	Transform triangleTransform;
};
