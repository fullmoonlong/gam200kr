/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/09/26
*/
#pragma once
#include <map>
#include <vector>
#include "System.h"
#include "Object.h"

class ObjectFactory : public System {
public:
	ObjectFactory();
	~ObjectFactory();

	void Initialize() override {}
	void Update() override;

	void Destroy(Object* object);

	void GiveObjectID(Object* object);

	int GetObjectID(int id);
	Object* CreateEmptyObject();

	void DestroyAllObjects();

	Object* FindObjectwithName(std::string& name);
	Object* FindObjectwithID(ObjectID id);


	std::map<ObjectID, Object*> GetObjecteList() { return objectIDMap; };

	Object* CreateDynamicObject();

private:
	std::map<ObjectID, Object*> objectIDMap;
	std::vector<Object*> objectsToBeDeleted;

	ObjectID lastObjectID = 0;
};

extern ObjectFactory* OBJECTFACTORY;