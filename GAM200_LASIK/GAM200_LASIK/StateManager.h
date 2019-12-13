#pragma once
#include "System.h"
#include "LevelSystem.h"
#include "OpenGLWindow.hpp"
#include <vector>
#include "EventHandler.hpp"

enum GameLevels {
	MAINMENU,
	LVTest1,
	LVTest2
};

class StateManager : public System, public SimpleEventHandler
{
public:
	StateManager(OpenGLWindow* window, float* dt);
	~StateManager();
	void Initialize() override;
	void Update(float dt) override;

	LevelSystem* GetCurrentLevel() { return levels.at(currentLevel); }
	void SetCurrentLevel(GameLevels currentLevel);
	GameLevels currentLevel;

	std::vector<LevelSystem*> levels;

	OpenGLWindow* windowPoint;
	float* deltaTime;
};
extern StateManager* STATEMANAGER;