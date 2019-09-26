/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/
#include "Engine.h"
#include "Application.h"
#include "ObjectFactory.h"

Engine* gameEngine = nullptr;

Engine::Engine()
{
	gamestate = GameState::PLAY;
	gameEngine = this;
}

Engine::~Engine()
{
	gameEngine = nullptr;
}

void Engine::Initialize()
{
	AddSystem(new Application());
	AddSystem(new ObjectFactory());
	for (auto sys : systems)
	{
		sys->Initialize();
	}
}

void Engine::Update()
{
	while (gamestate != GameState::EXIT)
	{
		for (auto sys : systems)
		{
			sys->Update();
		}
	}
}

void Engine::Shutdown()
{
	gamestate = GameState::EXIT;
}

void Engine::Run()
{
	Initialize();
	Update();
}

void Engine::AddSystem(System * system)
{
	systems.push_back(system);
}

void Engine::DestroyAllsystems()
{
	for (unsigned i = 0; i < systems.size(); ++i)
	{
		delete systems[systems.size() - 1 - i];
	}
}
