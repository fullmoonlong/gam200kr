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
#include "EventHandler.hpp"
#include "ShapeDrawingDemo.h"

class Demo : public SimpleEventHandler
{
public:
	//enum class DEMOINDEX
	//{
	//	SHAPEDRAWING
	//};

	Demo();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void ShutDown() = 0;
	
	bool IsRunning() const;

	void HandleKeyPress(KeyboardButtons button) override;
private:
	bool isRunning = false;
protected:
	Camera camera;
	CameraView view;

	
	//DEMOINDEX demoIndex = DEMOINDEX::SHAPEDRAWING;
	//ShapeDrawingDemo shapeDrawingDemo;
};