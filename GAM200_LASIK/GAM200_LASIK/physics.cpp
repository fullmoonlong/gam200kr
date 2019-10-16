#include "physics.h"

void Physics::Initialize(Math::vec2<float> position)
{
	transform->GetPosition() += GetVelocity() * dt;

}

Math::vec2<float> Physics::AddForce(float x, float y)
{
}

void Physics::AddForce(const Math::vec2<float> force)
{
}
