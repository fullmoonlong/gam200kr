/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
			Doyeong Yi doyoung.lee@digipen.edu
 *	GAM200 Engine Prototype
 *	2019/07/04
 */

#pragma once
#include <glfw3.h>
#include "OpenGL_Window.h"

enum class GameState { PLAY, EXIT }; //enum for gamestate

class Application
{
public:
	Application();
	~Application();
	void Initialize();
	void Update();
	void Shutdown();
	void Run(); //for game run
private:
	glWindow glWindow;
	GameState gameState; //gamestate
	int screenWidth = 800;
	int screenHeight = 600;
};