#pragma once
#include <string>
#include <Math/vec2.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Transform.hpp>

typedef unsigned int ObjectID;

class Object
{
public:
	friend class ObjectFactory;
	
	Object();
	~Object() = default;

	void Initialize(vec2<float> starting_position, float width, float height) noexcept;
	void Update(float dt) noexcept;
	Object* Clone();

	ObjectID GetObjectID(){	return objectID;}
	void SetObjectID(ObjectID objID){ objectID = objID;}

	int GetObjectCopyID() { return objectCopyId; }

	std::string GetName() const{return objectName;}
	void SetName(const std::string& name){objectName = name;}

	float GetXposition() { return position.x; };
	float GetYposition() { return position.y; };

	Transform transform;


	// Collision
	vec2<float> min;
	vec2<float> max;

	vec2<float> speed;

	bool isCollideWith(Object& object) noexcept;
	bool isCollideWithMouse(vec2<float>& mouse_position, int width, int height) noexcept;
	bool isMouseCollide = false;

private:
	ObjectID objectID;
	int objectCopyId = 0;
	std::string objectName = "";
	vec2<float> position;
	vec2<float> size;
};