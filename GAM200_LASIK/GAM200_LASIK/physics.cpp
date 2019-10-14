#include "physics.h" 
#include "Application.h" 
#include<SFML/Graphics.hpp>


Physics_object::Physics_object()
{
	position.x = 0;
	position.y = 0;
	m_velocity = 0;
	acceleration = 0;
}


void Physics_object::Initialize(const Math::vec2<float> position)
{
	
}

void Physics_object::SetVelocity(float x_velocity, float y_velocity) {
	m_velocity.x = x_velocity;
	m_velocity.y = y_velocity;
}

void Physics_object::SetGravity(float gravityAcc = -9.8f)
{
	/*SetVelocity(0, gravityAcc);*/
		//key pressed됐을때 밑으로가게하는거 판정하기

	
}

void Physics_object::integrate()
{
	if (m_inverseMass <= 0.0f) return;

	AddForce(m_velocity);

	Math::vec3 resultingAcc = acceleration;

}

Math::vec2<float> Physics_object::AddForce(Math::vec2<float> position)
{
	position.x += m_velocity.x;
	position.y += m_velocity.y;
	return position;
}