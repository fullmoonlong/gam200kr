#include "StateManager.h"
#include "MainMenu.h"
#include "LevelTest1.h"
#include <iostream>

StateManager* STATEMANAGER = nullptr;

StateManager::StateManager(OpenGLWindow* window, float* dt)
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
	currentLevel = GameLevels::MAINMENU;
	levels.push_back(new MainMenu(windowPoint));
	levels.push_back(new LevelTest1(windowPoint));
	levels.at(currentLevel)->Initialize();
}

void StateManager::Update(float dt)
{
	levels.at(currentLevel)->Update(dt);
}

void StateManager::SetCurrentLevel(GameLevels changeLevel)
{
	currentLevel = changeLevel;
	levels.at(currentLevel)->Initialize();
}
