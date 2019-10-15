/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Camera.hpp
*	
*	Implementing camera
*	
*	2019/10/10
*/


#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class [[nodiscard]]Camera
{
public:
	Camera(glm::vec2 camera_center, glm::vec2 camera_up) noexcept;

	glm::vec2 GetCenter() const noexcept { return center; }
	void    SetCenter(glm::vec2 camera_center) noexcept { center = camera_center; }
	glm::vec2 GetUp() const noexcept { return up; }
	glm::vec2 GetRight() const noexcept { return right; }

	void ResetUp(glm::vec2 camera_up = {0, 1}) noexcept;

	void MoveUp(float distance) noexcept;
	void MoveRight(float distance) noexcept;
	void Rotate(float angle_radians) noexcept;

	glm::mat3 CameraToWorld() const noexcept;
	glm::mat3 WorldToCamera() const noexcept;
	
	glm::vec2 rotate_by(float angle_in_radians, glm::vec2 v) noexcept
	{
		float cos_value = cos(angle_in_radians);
		float sin_value = sin(angle_in_radians);
		return glm::vec2{ cos_value* v.x - sin_value * v.y, sin_value* v.x + cos_value * v.y };
	}

private:
	glm::vec2 center{};
	glm::vec2 up{0.f , 1.f};
	glm::vec2 right{1.f, 0.f};
};

