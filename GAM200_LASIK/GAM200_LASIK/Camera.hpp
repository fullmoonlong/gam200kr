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
#include <vec2.hpp>
#include <mat3.hpp>

class [[nodiscard]]Camera
{
public:
	Camera(Math::vec2<float> camera_center, Math::vec2<float> camera_up) noexcept;

	Math::vec2<float> GetCenter() const noexcept { return center; }
	void    SetCenter(Math::vec2<float> camera_center) noexcept { center = camera_center; }
	Math::vec2<float> GetUp() const noexcept { return up; }
	Math::vec2<float> GetRight() const noexcept { return right; }

	void ResetUp(Math::vec2<float> camera_up = {0, 1}) noexcept;

	void MoveUp(float distance) noexcept;
	void MoveRight(float distance) noexcept;
	void Rotate(float angle_radians) noexcept;

	Math::mat3<float> CameraToWorld() const noexcept;
	Math::mat3<float> WorldToCamera() const noexcept;
	
private:
	Math::vec2<float> center;
	Math::vec2<float> up;
	Math::vec2<float> right;
	
};

