/**************************************************************************************
*	File Name        : Object.h
*	Project Name     : Keyboard Warriors
*	Primary Author   : Doyeong Yi
*	Secondary Author : Jookyung Lee
*	Copyright Information :
*    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
**************************************************************************************/

#pragma once
#include <string>
#include "vec2.hpp"
#include "Image.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Vertices.h"
#include "Mesh.h"
#include "Draw.hpp"
#include "Animation.hpp"
#include "PATH.hpp"
#include "Component.h"
#include "ComponentType.h"

typedef unsigned int ObjectID;

class Object
{
public:
	friend class ObjectFactory;

	Object();
	Object(const Object& rhs);
	~Object() = default;

	void Initialize(const char* name) noexcept;
	void Update(float dt) noexcept;
	Object* Clone() const;

	void SetObjectID(ObjectID objectID_) { objectID = objectID_; }
	ObjectID GetObjectID(){	return objectID;}

	std::string GetName() const{return objectName;}
	void SetName(const std::string& name){objectName = name;}

	float GetXposition() { return position.x; };
	float GetYposition() { return position.y; };

	void ChangeUnitAnimation();

	Transform transform;
	Material material;
	Animation animation;

	bool isCollideWith(Object& object) noexcept;
	bool isObjectInAttackRange(Object& object) noexcept;
	bool isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept;
	bool isMouseCollide = false;

	template <typename ComponentType>
	bool HasComponent()
	{
		for (auto list : componetList)
		{
			if (typeid(*list).name() == typeid(ComponentType).name())
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
		ComponentType* componentType = new ComponentType();
		dynamic_cast<Component*>(componentType)->SetOwner(this);
		this->componetList.push_back(componentType);
	}

	template<typename ComponentType>
	ComponentType* GetComponent()
	{
		for (auto list : componetList)
		{
			if (typeid(*list).name() == typeid(ComponentType).name())
				return dynamic_cast<ComponentType*>(list);
		}
		return nullptr;
	}

private:
	ObjectID objectID;
	std::string objectName = "";

	vec2<float> position;
	vec2<float> size;

	vec2<float> min;
	vec2<float> max;
	vec2<float> speed;

	std::vector <Component*>componetList;
};