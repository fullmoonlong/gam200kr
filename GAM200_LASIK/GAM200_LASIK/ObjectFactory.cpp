/**************************************************************************************
*	File Name        : ObjectFactory.cpp
*	Project Name     : Keyboard Warriors
*	Primary Author   : Doyeong Yi
*	Secondary Author :
*	Copyright Information :
*    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
**************************************************************************************/

#include "Object.h"
#include <iostream>
#include <stdlib.h>
#include "Sound.hpp"
#include "ObjectFactory.h"
#include "UnitStateComponent.hpp"

extern ObjectFactory* OBJECTFACTORY = nullptr;

ObjectFactory::ObjectFactory()
{
	std::cout << "ObjectFactory Add Successful" << std::endl;
	OBJECTFACTORY = this;
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::Update(float /*dt*/)
{
	for (auto object : objectsToBeDeleted)
	{
		if (object == nullptr)
		{
			continue;
		}
		auto objID = objectIDMap.find(object->objectID);
		if (objID != objectIDMap.end())
		{
			delete object;
			objectIDMap.erase(objID);
		}
	}
	objectsToBeDeleted.clear();
}

void ObjectFactory::Destroy(Object* object)
{
	objectsToBeDeleted.push_back(object);
}

void ObjectFactory::GiveObjectID(Object* object)
{
	object->objectID = lastObjectID;
	objectIDMap[lastObjectID] = object;
	lastObjectID++;
}

int ObjectFactory::GetObjectID(int id)
{
	return objectIDMap[id]->objectID;
}

Object* ObjectFactory::CreateEmptyObject()
{
	Object* object = new Object();
	GiveObjectID(object);
	return object;
}

void ObjectFactory::DestroyAllObjects()
{
	lastObjectID = 0;
	for (auto object : objectIDMap)
	{
		delete object.second;
	}
	objectIDMap.clear();
}

Object* ObjectFactory::FindObjectwithName(const std::string& name)
{
	for (auto object : objectIDMap)
	{
		if (object.second->objectName == name)
			return object.second;
	}
	return nullptr;
}

Object* ObjectFactory::FindObjectwithID(ObjectID id)
{
	for (auto object : objectIDMap)
	{
		if (object.second->objectID == id)
			return object.second;
	}
	return nullptr;
}