#pragma once
#include <string>
#include "vec2.hpp"
#include "Image.hpp"
#include "Transform.hpp"
#include "Vertices.h"
#include "Mesh.h"
#include "Draw.hpp"
#include "Animation.hpp"
#include "PATH.hpp"
#include "Component.h"
#include "ComponentType.h"

enum UnitType {
	Player,
	Enemy,
	ProjectilesPlayer,
	ProjectilesEnemy
};

enum State {
	WALK,
	ATTACK,
	IDLE
};


typedef unsigned int ObjectID;

class Object
{
public:
	friend class ObjectFactory;
	
	Object();
	~Object() = default;

	void Initialize(const char* name) noexcept;
	void Update(float dt) noexcept;
	Object* Clone();

	ObjectID GetObjectID(){	return objectID;}
	void SetObjectID(ObjectID objID){ objectID = objID;}

	std::string GetName() const{return objectName;}
	void SetName(const std::string& name){objectName = name;}

	float GetXposition() { return position.x; };
	float GetYposition() { return position.y; };

	UnitType GetType() { return unitType; }
	void SetType(UnitType unittype) { unitType = unittype; };

	State GetState() { return state; }
	void SetState(State state_) { state = state_; };

	vec2<float> GetAttackRange() const { return attackRange; }
	void SetAttackRange(vec2<float> attackrange) { attackRange = attackrange; }

	bool GetAttackState() { return attackState; }
	void SetAttackState(bool attackstate) { attackState = attackstate; };

	bool GetSpriteChangeState() { return spriteChange; }
	void SetSpriteChangeState(bool spritestate) { spriteChange = spritestate; };

	int GetHealth() { return health; }
	void SetHealth(int health_) { health = health_; };

	int GetDamage() { return damage; }
	void SetDamage(int damage_) { damage = damage_; };

	void ChangeUnitAnimation();

	Transform transform;
	Material material;
	Mesh mesh;
	Vertices vertices;
	Animation animation;
	Image image;


	// Collision
	vec2<float> min;
	vec2<float> max;
	
	int health;
	int damage;

	vec2<float> attackRange = {0, 0};
	vec2<float> speed;

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

	UnitType unitType;
	State state;
	bool attackState = false;
	bool spriteChange = false;

	float baseTime = 0.f;

	std::vector <Component*>componetList;
};