/**************************************************************************************
 *	File Name        : System.h
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once

class System
{
public:
	virtual void Initialize() {};
	virtual void Update(float dt) = 0;
	virtual ~System() {};
};