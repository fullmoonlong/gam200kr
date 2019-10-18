#include "physics.h"

void Physics::Initialize(Math::vec2<float> position)
{

}

void Physics::AddForce(float x, float y)
{
	Transform * m_transform = nullptr;
	m_transform->GetPosition() += GetVelocity() * dt;

}

const Math::vec2<float> Physics::GetVelocity()
{
	return m_body->m_velocity;
}

void Physics::SetVelocity(const Math::vec2<float> velocity)
{
	m_body->m_velocity = velocity;
}

//void Physics::AddForce(const Math::vec2<float> force)
//{
//}

bool Physics::AABBvsAABB(AABB a, AABB b)
{
	if (a.max.x < b.min.x or a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y or a.min.y > b.max.y) return false;

	return true;
}
