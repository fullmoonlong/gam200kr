/**************************************************************************************
 *	File Name        : Engine.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

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
