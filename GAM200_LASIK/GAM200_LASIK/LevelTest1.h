#pragma once
#include "LevelSystem.h"
#include "ObjectFactory.h"
class LevelTest1 : public LevelSystem
{
public:
	LevelTest1();
	~LevelTest1();
	void Initialize() override;
	void Update() override;
	void Shutdown() override;
private:
	Object * test;
};