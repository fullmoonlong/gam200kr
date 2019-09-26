/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
 *	GAM200 Engine Prototype
 *	2019/07/04
 */

#pragma once
#include <glfw3.h>
#include "OpenGL_Window.h"
#include "System.h"
#include "Engine.h"

class Application : public System
{
public:
	Application();
	~Application();
	void Initialize(void) override;
	void Update() override;

private:
	glWindow glWindow;
	int screenWidth = 800;
	int screenHeight = 600;
};