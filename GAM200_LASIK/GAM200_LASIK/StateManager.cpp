#include "StateManager.h"
#include "LevelTest1.h"
#include "LevelTest2.h"
#include <iostream>

StateManager* STATEMANAGER = nullptr;

StateManager::StateManager()
{
	STATEMANAGER = this;
	std::cout << "StateManager Add Sucessful" << std::endl;
}

StateManager::~StateManager()
{
}

void StateManager::Initialize()
{
	currentLevel = GameLevels::LVTest1;
	levels.push_back(new LevelTest1());
	levels.push_back(new LevelTest2());
	levels.at(currentLevel)->Initialize();
}

void StateManager::Update()
{
	levels.at(currentLevel)->Update();
}

void StateManager::SetCurrentLevel(GameLevels changeLevel)
{
	currentLevel = changeLevel;
	levels.at(currentLevel)->Initialize();
}
