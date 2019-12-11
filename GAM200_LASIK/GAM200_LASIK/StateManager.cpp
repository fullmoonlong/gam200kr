#include "StateManager.h"
#include "LevelTest1.h"
#include <iostream>

StateManager* STATEMANAGER = nullptr;

StateManager::StateManager(Window* window, float* dt)
{
	STATEMANAGER = this;
	windowPoint = window;
	deltaTime = dt;
	std::cout << "StateManager Add Sucessful" << std::endl;
}

StateManager::~StateManager()
{
}

void StateManager::Initialize()
{
	currentLevel = GameLevels::LVTest1;
	levels.push_back(new LevelTest1(windowPoint));
	levels.at(currentLevel)->Initialize();
}

void StateManager::Update()
{
	levels.at(currentLevel)->Update(*deltaTime);
}

void StateManager::SetCurrentLevel(GameLevels changeLevel)
{
	currentLevel = changeLevel;
	levels.at(currentLevel)->Initialize();
}
