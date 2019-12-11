#pragma once
#include "EventHandler.hpp"

class LevelSystem : public SimpleEventHandler
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Shutdown() = 0;
};