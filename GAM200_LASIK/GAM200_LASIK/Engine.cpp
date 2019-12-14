/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/
#include "Engine.h"
#include "Application.h"
#include "ObjectFactory.h"
#include "StateManager.h"
#include "Sound.hpp"


Engine* gameEngine = nullptr;

Engine::Engine()
{
	gameEngine = this;
	gamestate = GameState::PLAY;
}

Engine::~Engine()
{
	//ENGINE = nullptr;
	DestroyAllsystems();
	delete gameEngine;
}

void Engine::Initialize()
{
	AddSystem(new Application());
	AddSystem(new ObjectFactory());

	Application* app = dynamic_cast<Application*>(systems[0]);
	AddSystem(new StateManager(app->GetWindow(), app->GetDeltaTime()));
	AddSystem(new SoundManager());
	for (auto sys : systems)
	{
		sys->Initialize();
	}
}

void Engine::Update()
{
	while (gamestate != GameState::EXIT)
	{
		clock.UpdateClock();
		for (auto sys : systems)
		{
			sys->Update(deltaTime);
		}
		deltaTime = clock.GetTimeFromLastUpdate();
	}
	Shutdown();
}

void Engine::Shutdown()
{
	DestroyAllsystems();
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
