/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/26
*/
#include "ObjectFactory.h"
#include "Object.h"
#include <iostream>

extern ObjectFactory* OBJECTFACTORY = nullptr;

ObjectFactory::ObjectFactory()
{
	std::cout << "ObjectFactory Add Successful" << std::endl;
	OBJECTFACTORY = this;
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
	object->objectID = lastObjectID;
	objectIDMap[lastObjectID] = object;
	lastObjectID++;
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

Object* ObjectFactory::FindObjectwithName(std::string& name)
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

Object* ObjectFactory::CreateDynamicObject()
{


	return  a;
}
