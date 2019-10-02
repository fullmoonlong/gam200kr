#pragma once
#include "LevelSystem.h"

class LevelTest2 : public LevelSystem
{
public:
	LevelTest2();
	~LevelTest2();
	void Initialize() override;
	void Update() override;
	void Shutdown() override;
};