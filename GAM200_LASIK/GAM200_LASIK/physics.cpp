#include "Physics.h" 
#include "Application.h" 
//#include<SFML/Graphics.hpp>


Physics_object::Physics_object()
{
	position.x = 0;
	position.y = 0;
	m_velocity = 0;
	acceleration = 0;
}


void Physics_object::Initialize(Math::vec2<float> new_position)
{
	new_position.x = 0.f;
	new_position.y = 0.f;
}

void Physics_object::SetVelocity(float x_velocity, float y_velocity) {
	m_velocity.x = x_velocity;
	m_velocity.y = y_velocity;
}

void Physics_object::SetGravity(float gravityAcc)
{
	gravityAcc;
}

void Physics_object::Integrate()
{
	if (m_inverseMass <= 0.0f) return;

	AddForce(m_velocity);

	Math::vec3 resultingAcc = acceleration;

}

Math::vec2<float> Physics_object::AddForce(Math::vec2<float> v)
{
	v.x += m_velocity.x;
	v.y += m_velocity.y;
	return position;
}