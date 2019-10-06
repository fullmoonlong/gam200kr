#include "Physics.h" 
#include "Application.h" 
#include<SFML/Graphics.hpp>

Physics_object::Physics_object()
{

}

Physics_object::~Physics_object()
{

}

void Physics_object::Initialize(const MathLibrary::vec2 & xPosition, float mass)
{
	m_mass = mass;
	m_xPosition = xPosition;
}

void Physics_object::Update(float dt)
{

}

void Physics_object::Acceleration(const MathLibrary::vec2 & f, float dt)
{
	if (Unmove()) return;

	m_xDisplacement += f * (m_inverseMass * dt * dt);
}

//void Physics_object::BoxCollision() 
//{ 
// 
//} 
// 
//void Physics_object::CircleCollision() 
//{ 
// 
//}