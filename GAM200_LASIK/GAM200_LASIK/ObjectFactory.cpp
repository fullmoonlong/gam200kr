/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/26
*/
#include "ObjectFactory.h"
#include "Object.h"
#include <iostream>

extern ObjectFactory* objectFactory = nullptr;

ObjectFactory::ObjectFactory()
{
	std::cout << "ObjectFactory Add Sucessful" << std::endl;
	objectFactory = this;
	lastObjectID = 0;
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::Update()
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

void ObjectFactory::Destroy(Object * object)
{
	objectsToBeDeleted.push_back(object);
}

void ObjectFactory::GiveObjectID(Object * object)
{
	lastObjectID++;
	object->objectID = lastObjectID;
	objectIDMap[lastObjectID] = object;
}

int ObjectFactory::GetObjectID(int id)
{
	return objectIDMap[id]->objectID;
}

Object * ObjectFactory::CreateEmptyObject()
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
