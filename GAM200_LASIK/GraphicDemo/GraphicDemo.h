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
	bool isRunning();
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override final;
	void HandleWindowClose() override final;
	void HandleResizeEvent(const int& width, const int& height) override final;
	void HandleScrollEvent(float scroll_amount) override final;
private:
	bool running;
	Window window;
	const int width = 1280;
	const int height = 720;

	Camera camera;
	CameraView view;
	
	Shader shader;
	Mesh rectangle;
	Mesh line;
	Vertices vertices;
	Vertices lineVertices;
	Transform transform;
	Transform lineTransform;
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::Color };
};
