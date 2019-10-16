#include "CameraTransform.hpp"

//operator* ->  Check later
glm::mat3 CameraTransform::GetModelToWorld() noexcept
{
	glm::mat3 worldMatrix;
	glm::mat3 translateMatrix = buildTranslation(translation);
	glm::mat3 rotationMatrix = buildRotation(rotation);
	glm::mat3 scaleMatrix = buildScaling(scale);

	worldMatrix = translateMatrix * rotationMatrix * scaleMatrix;

	if (parent != nullptr)
	{
		return parent->GetModelToWorld() * worldMatrix;
	}
	return worldMatrix;
}

glm::mat3 CameraTransform::GetWorldToModel() noexcept
{
	glm::mat3 modelMatrix;
	glm::mat3 translateMatrix = buildTranslation(translation);
	glm::mat3 rotationMatrix = buildRotation(rotation);
	glm::mat3 scaleMatrix = buildScaling(scale);

	modelMatrix = scaleMatrix * rotationMatrix * translateMatrix;

	if (parent != nullptr)
	{
		return parent->GetWorldToModel() * modelMatrix;
	}
	return modelMatrix;
}

float CameraTransform::CalculateWorldDepth() const noexcept
{
	float sum = 0;
	sum = depth;
	if (parent != nullptr)
	{
		return sum + parent->CalculateWorldDepth();
	}
	return sum;
}
