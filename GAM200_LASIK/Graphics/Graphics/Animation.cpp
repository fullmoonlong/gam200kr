/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Animation.cpp
 *	
 *	Animation class
 *	
 *	2019/11/01
 */

#include "Animation.hpp"

void Animation::Initialize(int new_count, Shader& new_shader)
{
	shader = new_shader;
	frameCount = new_count;
	animateSpeed = 10.0f;
}

void Animation::Animate(float dt)
{
	Shader::UseShader(shader);
	shader.SendUniformVariable("frameX", frameCount);
	shader.SendUniformVariable("frameIndex", frameIndex);
	shader.SendUniformVariable("correction", 0.003f);
	
	frameIndex = int(baseTime) % frameCount;
	baseTime += animateSpeed * dt;
}

void Animation::ChangeAnimation(int new_count)
{
	frameCount = new_count;
}
