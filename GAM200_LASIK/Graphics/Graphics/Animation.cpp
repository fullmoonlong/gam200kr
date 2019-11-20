/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Animation.hpp
 *	
 *	Animation class
 *	
 *	2019/11/01
 */

#include <GL/glew.h>
#include "Animation.hpp"
#include "Image.hpp"

void Animation::Initialize(Image& new_sprite, Mesh& new_shape, int new_count, Shader& new_shader)
{
	shader = new_shader;
	spriteSheet.LoadFromImage(new_sprite);
	shape = new_shape;
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

void Animation::ChangeAnimation(const std::filesystem::path& new_sprite, int new_count)
{
	frameCount = new_count;
	spriteSheet.LoadFromImage(new_sprite);
}
