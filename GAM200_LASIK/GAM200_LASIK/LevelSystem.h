/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/10/02
*/
#pragma once
#include "EventHandler.hpp"

class LevelSystem : public SimpleEventHandler
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Shutdown() = 0;
};