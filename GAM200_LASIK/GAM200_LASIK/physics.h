#pragma once 
#include "Application.h" 
#include "Object.h"
#include "../math_lib/include/vec2.hpp"
#include "../math_lib/include/vec3.hpp"
#include"body.h"
#include"Transform.h"
#include <ctime>

class Body;

struct AABB {
	Math::vec2<float> min;
	Math::vec2<float> max;
};

struct Circle {
	float radius;
	Math::vec2<float> position;
};


class Pair {
public:
	Pair(Body* A, Body* B) : m_A(A), m_B(B) {}

	Body * m_A;
	Body* m_B;
};

class Physics {

	friend class Transform;

	Body* m_body;

	Physics();

	void Initialize(Math::vec2<float> position);

	//void integrate();

	void AddForce(float x, float y);

	const Math::vec2<float> GetVelocity();

	void SetVelocity(const Math::vec2<float> velocity);

	//void AddForce(const Math::vec2<float> force);

	bool AABBvsAABB(AABB a, AABB b);
};

//class GravityOb :public Physics {
//
//};
//
//class Static_physisOb : Physics {
//
//};