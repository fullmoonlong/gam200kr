/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/25
*/
#include "Object.h"
#include <iostream>

Object::Object()
{
	objectID = 0;
}

Object::~Object()
{
	for (auto componentList : mComponetList)
	{
		delete componentList;
	}
	mComponetList.clear();
}

void Object::Initialize()
{
	std::cout << "Object Initialize" << std::endl;
	for (auto components : this->mComponetList)
	{
		components->Initialize();
	}
}

void Object::Update()
{
	std::cout << "Object Update" << std::endl;
	for (auto components : this->mComponetList)
	{
		components->Update();
	}
}
