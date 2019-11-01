#include "Transform.hpp"

mat3<float> Transform::GetModelToWorld() noexcept
{
	mat3<float> M;
	mat3<float> T = build_translation(translation.x, translation.y);
	mat3<float> R = build_rotation(rotation);
	mat3<float> S = build_scaling(scale.x, scale.y);

	M = T * R * S;

	if (parent != nullptr)
	{
		return parent->GetModelToWorld() * M;
	}
	return M;
}

mat3<float> Transform::GetWorldToModel() noexcept
{
	mat3<float> M;
	mat3<float> T = build_translation(translation.x, translation.y);
	mat3<float> R = build_rotation(rotation);
	mat3<float> S = build_scaling(scale.x, scale.y);

	M = T * R * S;

	if (parent != nullptr)
	{
		return parent->GetWorldToModel() * M;
	}
	return M;
}

float Transform::CalculateWorldDepth() const noexcept
{
	float sum = 0;
	sum = depth;
	if (parent != nullptr)
	{
		return sum + parent->CalculateWorldDepth();
	}
	return sum;
}
