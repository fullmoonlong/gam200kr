/********************************************************
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Application.h
*	
*	Graphic demo main file
*	
*	Nov.29 2019
*******************************************************/

#pragma once

/********************************************************
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Demo.h
*	
*	Graphic demo main file
*	
*	Nov.28 2019
*******************************************************/

#pragma once
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
#include "ShapeDrawingDemo.h"

class Application : public SimpleEventHandler
{
public:
	enum class DEMOINDEX
	{
		SHAPEDRAWING
	};

	Application();
	void Initialize();
	void Update();
	void ShutDown();

	bool IsRunning() const;

	void HandleKeyPress(KeyboardButtons button) override;
private:
	bool isRunning = false;
protected:
	Window window;
	Camera camera;
	CameraView view;
	const int width = 1280;
	const int height = 720;

	DEMOINDEX demoIndex = DEMOINDEX::SHAPEDRAWING;
	ShapeDrawingDemo shapeDrawingDemo;
};