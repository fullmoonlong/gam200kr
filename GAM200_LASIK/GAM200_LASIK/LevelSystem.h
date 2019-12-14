/**************************************************************************************
 *	File Name        : LevelSystem.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "EventHandler.hpp"

class LevelSystem : public SimpleEventHandler
{
public:
	virtual void Initialize() = 0;
	virtual void Update(float dt) = 0;
	virtual void Shutdown() = 0;
};