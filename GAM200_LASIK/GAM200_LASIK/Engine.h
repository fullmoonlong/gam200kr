/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/
#pragma once
#include <vector>

enum class GameState { PLAY, EXIT }; //enum for gamestate
class System;
class Engine
{
public:
	Engine();
	~Engine();

	void Initialize();
	void Update();
	void Shutdown();
	void Run();

	void AddSystem(System* system);
	void DestroyAllsystems();

private:
	std::vector<System*> systems;
	GameState gamestate;
};

extern Engine* gameEngine;
