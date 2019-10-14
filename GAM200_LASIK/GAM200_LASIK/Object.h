#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "ComponentType.h"

typedef unsigned int ObjectID;

struct position
{
	float x, y;
	position(float x_, float y_) : x(x_), y(y_) {}
};

class Object {
public:
	friend class ObjectFactory;
	Object();
	~Object();

	void Initialize();
	void Update();
	//void Render();

	ObjectID GetObjectID(){	return objectID;}
	void SetObjectID(ObjectID objID){ objectID = objID;}

	std::string GetName() const{return objectName;}
	void SetName(const std::string& name){objectName = name;}

	float GetXposition() { return xpos; };
	float GetYposition() { return ypos; };
	position SetPosition(float x, float y) { xpos = x; ypos = y; return position(xpos, ypos); }
	
	template <typename ComponentType>
	bool HasComponent()
	{
		for (auto componentList : mComponetList)
		{
			if (typeid(*componentList).name() == typeid(ComponentType).name())
				return true;
		}
		return false;

	}

	template<typename ComponentType>
	constexpr void AddComponent()
	{
		if (HasComponent<ComponentType>()) 
		{
			return;
		}
		ComponentType * componentType = new ComponentType();
		dynamic_cast<Component*>(componentType)->SetOwner(this);
		this->mComponetList.push_back(componentType);
	}

	template<typename ComponentType>
	ComponentType* GetComponent()
	{
		for (auto componentList : mComponetList)
		{
			if (typeid(*componentList).name() == typeid(ComponentType).name())
				return dynamic_cast<ComponentType*>(componentList);
		}
		return nullptr;

	}
private:
	ObjectID objectID;
	std::string objectName = "";
	float xpos;
	float ypos;
	std::vector <Component*>mComponetList;
};