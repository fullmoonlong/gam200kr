/**************************************************************************************
 *	File Name        : ObjectFactory.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

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
	void Update(float dt) override;

	void Destroy(Object* object);

	void GiveObjectID(Object* object);

	int GetObjectID(int id);
	Object* CreateEmptyObject();

	ObjectID GetLastObjectID() { return lastObjectID; }

	void DestroyAllObjects();

	Object* FindObjectwithName(const std::string& name);
	Object* FindObjectwithID(ObjectID id);

	std::map<ObjectID, Object*> GetObjecteList() { return objectIDMap; };
	std::vector<Object*> GetPlayerObjecteList() { return PlayerUnits; };
	std::vector<Object*> GetEnemyObjecteList() { return EnemyUnits; };

	void CopyObject(Object* object);

	void CheckCollision();
	void CheckAttackState();
	void DamageTest(int time);

private:
	std::map<ObjectID, Object*> objectIDMap;

	std::vector<Object*> PlayerUnits;
	std::vector<Object*> EnemyUnits;

	std::vector<Object*> objectsToBeDeleted;

	ObjectID lastObjectID = 0;
	int PlayerAmount = 0;
	int EnemyAmount = 0;
};

extern ObjectFactory* OBJECTFACTORY;