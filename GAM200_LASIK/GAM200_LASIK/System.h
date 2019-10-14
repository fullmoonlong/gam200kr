/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/
#pragma once

class System
{
public:
	virtual void Initialize() {};
	virtual void Update() = 0;
	virtual ~System() {};
};