/**************************************************************************************
 *	File Name        : StateManager.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <vector>
#include "System.h"
#include "LevelSystem.h"
#include "OpenGLWindow.hpp"
#include "EventHandler.hpp"

enum GameLevels {
	LOGO,
	MAINMENU,
	LEVELSELECT,
	TUTORIAL,
	LVTest1
};

class StateManager : public System, public SimpleEventHandler
{
public:
	StateManager(OpenGLWindow* window);
	~StateManager();
	void Initialize() override;
	void Update(float dt) override;

	LevelSystem* GetCurrentLevel() { return levels.at(currentLevel); }
	void SetCurrentLevel(GameLevels currentLevel);
	GameLevels currentLevel;

	std::vector<LevelSystem*> levels;

	OpenGLWindow* windowPoint;
};
extern StateManager* STATEMANAGER;