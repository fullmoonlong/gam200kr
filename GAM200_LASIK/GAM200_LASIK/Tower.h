#pragma once
/**************************************************************************************
 *	File Name        : Tower.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Object.h"
#include <vec2.hpp>
#include "UnitStateComponent.hpp"

class Tower : public Object {
public:
	void UnitInitialize(const char* name);

private:
	int         towerHealth = 300;
	int         towerDamage = 0;

};

class Lair : public Object {
public:
	void UnitInitialize(const char* name);

private:
	int         lairHealth = 300;
	int         lairDamage = 0;

};