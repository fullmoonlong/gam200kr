#pragma once
#include "System.h"
#include "LevelSystem.h"
#include "OpenGL_Window.h"
#include <vector>

enum GameLevels {
	LVTest1,
	LVTest2
};

class StateManager : public System
{
public:
	StateManager(Window* window, float* dt);
	~StateManager();
	void Initialize() override;
	void Update() override;

	void SetCurrentLevel(GameLevels currentLevel);
	GameLevels currentLevel;

	std::vector<LevelSystem*> levels;

	Window* windowPoint;
	float* deltaTime;
};
extern StateManager* STATEMANAGER;