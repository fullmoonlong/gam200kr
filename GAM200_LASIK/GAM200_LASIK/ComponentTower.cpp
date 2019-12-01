#include "ComponentTower.h"
#include "ObjectFactory.h"

LairComponent::~LairComponent()
{
}

void LairComponent::Initialize()
{
}

void LairComponent::SpawnEnemy(Object* obj, float dt)
{
	if (dt >= 1.0f)
	{
		time++;
	}
	
	if (time == 6)
	{
		OBJECTFACTORY->CopyObject(obj);
		time = 0;
	}
}
