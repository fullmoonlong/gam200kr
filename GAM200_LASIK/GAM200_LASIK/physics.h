#pragma once 
#include "Application.h" 
#include "Object.h"
#include "../math_lib/include/vec2.hpp"
#include "../math_lib/include/vec3.hpp"
#include<assert.h>


struct AABB {
	Math::vec2<float> min;
	Math::vec2<float> max;
};

struct Circle {
	float radius;
	Math::vec2<float> position;
};

class Physics_object {

	Physics_object();
	
	void Initialize(const Math::vec2<float> position, float fMass);

	void integrate();

	Math::vec2<float> AddForce(Math::vec2<float> position);

	void SetVelocity(float x_velocity , float y_velocity);

	void SetGravity(float gravityAcc = -9.8f);

protected:
	Math::vec2<float> position;
	Math::vec2<float> m_velocity;
	float acceleration;

	float m_damping;
	float m_inverseMass;
	float m_mass;

};

class GravityOb :public Physics_object {

};

class Static_physisOb : Physics_object {

};