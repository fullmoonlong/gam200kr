/**************************************************************************************
 *	File Name        : Engine.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Engine.h"
#include "Application.h"
#include "ObjectFactory.h"
#include "StateManager.h"
#include "GameManager.h"
#include "Sound.hpp"
#include "CurrencySystem.hpp"
#include "UpgradeSystem.hpp"

Engine* gameEngine = nullptr;

Engine::Engine()
{
	gameEngine = this;
	gamestate = GameState::PLAY;
}

Engine::~Engine()
{
	DestroyAllsystems();
	delete gameEngine;
}

void Engine::Initialize()
{
	AddSystem(new Application());
	Application* app = dynamic_cast<Application*>(systems[0]);

	AddSystem(new ObjectFactory());
	AddSystem(new SoundManager());
	AddSystem(new GameManager());
	AddSystem(new CurrencySystem());
	AddSystem(new UpgradeSystem());
	AddSystem(new StateManager(app->GetWindow()));
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

void Engine::AddSystem(System* system)
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
