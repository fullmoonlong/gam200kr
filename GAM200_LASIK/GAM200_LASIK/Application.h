/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
 *	GAM200 Engine Prototype
 *	2019/07/04
 */

#pragma once
#include "OpenGL_Window.h"
#include "System.h"
#include "Shader.h"
#include "EventHandler.h"

class Application : public EventHandler
{
public:
	Application();
	~Application();
	void Initialize(void);
	void Update();
	
	void HandleKeyTriggered(KeyboardButtons button) override;

private:
	Shader shader;
	glWindow glWindow;
	int screenWidth = 800;
	int screenHeight = 600;
	bool isTriggered = false;
};
