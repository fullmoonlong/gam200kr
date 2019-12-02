/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Animation.hpp
 *	
 *	Animation class
 *	
 *	2019/11/01
 */

#pragma once
#include "Shader.h"

class Animation
{
public:
	Animation() = default;

	void Initialize(int new_count, Shader& new_shader);
	void Animate(float dt);
	void ChangeAnimation(int new_count);
private:
	Shader shader;
	int frameCount;
	int frameIndex = 0;
	float animateSpeed;
	float baseTime = 0.0f;
};
