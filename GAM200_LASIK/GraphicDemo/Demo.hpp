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
#include "Camera.hpp"
#include "CameraView.hpp"
#include "EventHandler.hpp"

class Demo : public SimpleEventHandler
{
public:
	//enum class DEMOINDEX
	//{
	//	SHAPEDRAWING
	//};

	explicit Demo(Window& window)
		: width(window.GetWindowWidth()), height(window.GetWindowHeight()) {}
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void ShutDown() = 0;

	void HandleKeyPress(KeyboardButton button) override;
	void HandleResizeEvent(const int& width, const int& height) override;
protected:
	Camera camera;
	CameraView view;
	int width;
	int height;
	
	//DEMOINDEX demoIndex = DEMOINDEX::SHAPEDRAWING;
	//ShapeDrawingDemo shapeDrawingDemo;
};