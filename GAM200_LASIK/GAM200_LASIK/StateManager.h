#pragma once
#include "System.h"
#include "LevelSystem.h"
#include <vector>

enum GameLevels {
	LVTest1,
	LVTest2
};

class StateManager : public System
{
public:
	StateManager();
	~StateManager();
	void Initialize() override;
	void Update() override;

	void SetCurrentLevel(GameLevels currentLevel);
	GameLevels currentLevel;

	std::vector<LevelSystem*> levels;
};
extern StateManager* STATEMANAGER;