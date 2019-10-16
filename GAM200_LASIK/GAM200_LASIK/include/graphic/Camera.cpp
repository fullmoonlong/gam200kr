/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Camera.cpp
*	
*	Implementing camera
*	
*	2019/10/10
*/


#include "Camera.hpp"
#include "CameraTransform.hpp"

void Camera::ResetUp(glm::vec2 camera_up) noexcept
{
	up.x = camera_up.x;
	up.y = camera_up.y;
	right = { up.y, -up.x };
}

void Camera::MoveUp(float distance) noexcept
{
	center += glm::normalize(up) * distance;
}

void Camera::MoveRight(float distance) noexcept
{
	center += glm::normalize(right) * distance;
}

void Camera::Rotate(float angle_radians) noexcept
{
	up = rotate_by(angle_radians, up);
	right = rotate_by(angle_radians, right);
}

glm::mat3 Camera::CameraToWorld() const noexcept
{
	glm::mat3 inverseTransformMatrix = { up.y,  -right.y, (right.y * glm::dot(-up, center) - glm::dot(-right, center) * up.y),
								  -up.x, right.x,  (glm::dot(-right, center) * up.x - right.x * glm::dot(-up, center)),
								  0.0f,  0.0f,     1.0f };
	return transpose(inverseTransformMatrix);
}

glm::mat3 Camera::WorldToCamera() const noexcept
{
	glm::mat3 transformMatrix = {
			right.x, up.x, 0.0f,
			right.y, up.y, 0.0f,
			glm::dot(right, center), glm::dot(up, center),1.0f };
	return transformMatrix;
}
