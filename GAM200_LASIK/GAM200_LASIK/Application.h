/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*			Doyeong Yi doyoung.lee@digipen.edu
*	Application
*	2019/07/04
*/


#pragma once
#include "OpenGL_Window.h"
#include "Shader.h"
#include "EventHandler.hpp"
#include "Texture.hpp"
#include "Mesh.h"

class Application : public SimpleEventHandler
{
public:
	Application();
	~Application();
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override;
	void HandleKeyRelease(KeyboardButtons button) override;
	void HandleResizeEvent(const int& width, const int& height) override;
	
	bool isRunning = false;
	
private:
	Mesh rectangle;
	Texture texture;
	Shader shader;
	glWindow glWindow;
};
