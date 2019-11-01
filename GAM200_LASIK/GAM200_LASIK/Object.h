#pragma once
#include <string>
#include <vector>
#include <Math/vec2.hpp>
#include <Graphics/Image.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Transform.hpp>

typedef unsigned int ObjectID;

class Object
{
public:
	friend class ObjectFactory;
	
	Object();
	~Object() = default;

	void Initialize(vec2<float> starting_position) noexcept;
	void Update(float dt) noexcept;

	ObjectID GetObjectID(){	return objectID;}
	void SetObjectID(ObjectID objID){ objectID = objID;}

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
	bool isCollideWithMouse(vec2<float>& mouse, int width, int height) noexcept;

	bool isMouseCollide = false;

private:
	ObjectID objectID;
	std::string objectName = "";
	vec2<float> position;
	vec2<float> size;
};