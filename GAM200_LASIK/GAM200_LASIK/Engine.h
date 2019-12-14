/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/
#pragma once
#include <vector>
#include "Util/Clock.hpp"

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

	GameState gamestate;
private:
	std::vector<System*> systems;
	Clock clock;
	float deltaTime = 0;
};

extern Engine* gameEngine;
