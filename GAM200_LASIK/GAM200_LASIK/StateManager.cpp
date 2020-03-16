/**************************************************************************************
 *	File Name        : StateManager.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "StateManager.h"
#include "Logo.h"
#include "MainMenu.h"
#include "LevelSelect.h"
#include "Tutorial.h"
#include "LevelTest1.h"
#include "Upgrade.hpp"

StateManager* STATEMANAGER = nullptr;

StateManager::StateManager(OpenGLWindow* window)
{
	STATEMANAGER = this;
	windowPoint = window;
	std::cout << "StateManager Add Sucessful" << std::endl;
}

StateManager::~StateManager()
{
}

void StateManager::Initialize()
{
	currentLevel = GameLevels::LVTest1;
	levels.push_back(new Logo(windowPoint));
	levels.push_back(new MainMenu(windowPoint));
	levels.push_back(new LevelSelect(windowPoint));
	levels.push_back(new Tutorial(windowPoint));
	levels.push_back(new LevelTest1(windowPoint));
	levels.push_back(new Upgrade(windowPoint));
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
