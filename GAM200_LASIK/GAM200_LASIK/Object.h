#pragma once
#include <string>
#include <vector>
#include <math/vec2.hpp>
#include <graphic/Image.hpp>
#include <graphic/Texture.hpp>
#include <graphic/Transform.hpp>

typedef unsigned int ObjectID;

class Object
{
public:
	friend class ObjectFactory;
	struct Animation
	{
		int spriteCount = 0;
		std::vector<float> texCoord;
		Texture sprite;
		float baseTime;
	};
	
	Object();
	~Object();

	void Initialize(vec2<float> starting_position, int spriteCount) noexcept;
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
	Animation animation;
	ObjectID objectID;
	std::string objectName = "";
	vec2<float> position;
	vec2<float> size;
};