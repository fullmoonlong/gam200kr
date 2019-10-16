#pragma once
#include <glm.hpp>

class [[nodiscard]] CameraTransform
{
public:
	CameraTransform() noexcept = default;
	glm::mat3 GetModelToWorld() noexcept;
	glm::mat3 GetWorldToModel() noexcept;

	float CalculateWorldDepth() const noexcept;

	float GetDepth() const noexcept { return depth; }
	void SetDepth(float new_depth) noexcept { depth = new_depth; }

	glm::vec2 GetTranslation() const noexcept { return translation; }
	void SetTranslation(glm::vec2& new_translation) noexcept { translation = new_translation; }

	glm::vec2 GetScale() const noexcept { return scale; }
	void    SetScale(glm::vec2& new_scale) noexcept { scale = new_scale; }

	float GetRotation() const noexcept { return rotation; }
	void  SetRotation(float new_rotation) noexcept { rotation = new_rotation; }

	const CameraTransform* GetParent() const noexcept { return parent; }
	void SetParent(CameraTransform * transform_parent) noexcept { parent = transform_parent; }

	glm::mat3 buildTranslation(glm::vec2 translate) noexcept
	{
		return glm::mat3{ 1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			translate.x, translate.y, 1.f };
	}

	glm::mat3 buildRotation(float angle_in_radians) noexcept
	{
		return glm::mat3{ cos(angle_in_radians), sin(angle_in_radians), 0.f,
			-sin(angle_in_radians), cos(angle_in_radians), 0.f,
			0.f, 0.f, 1.f };
	}

	glm::mat3 buildScaling(glm::vec2 scale_) noexcept
	{
		return glm::mat3{ scale_.x, 0.f, 0.f,
			0.f, scale_.y, 0.f,
			0.f, 0.f, 1.f };
	}

private:
	glm::vec2 translation{};
	glm::vec2 scale{1.0f, 1.0f};
	float rotation = 0.0f;
	float depth = 0.0f;
	CameraTransform* parent = nullptr;
};