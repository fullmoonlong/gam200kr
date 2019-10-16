#pragma once 
#include "Application.h" 
#include "Object.h"
#include "../math_lib/include/vec2.hpp"
#include "../math_lib/include/vec3.hpp"
#include<assert.h>
#include"body.h"
#include"Transform.h"

class Body;

struct AABB {
	Math::vec2<float> min;
	Math::vec2<float> max;
};

struct Circle {
	float radius;
	Math::vec2<float> position;
};


class Pair{
public:
	Pair(Body* A, Body* B) : m_A(A), m_B(B) {}
	
	Body * m_A;
	Body* m_B;
};

class Physics {
	
	friend class Transform;

	Body* body;
	Transform * transform;

	Physics();
	
	void Initialize(Math::vec2<float> position);

	//void integrate();

	Math::vec2<float> AddForce(float x, float y);

	const Math::vec2<float> GetVelocity() { return body->m_velocity; }

	void SetVelocity(const Math::vec2<float> velocity) { body->m_velocity = velocity; }

	void AddForce(const Math::vec2<float> force);

};

class GravityOb :public Physics {

};

class Static_physisOb : Physics {

};