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

void Animation::Initialize(SpriteSheet new_sheet, const Shader& new_shader)
{
	spriteSheet = new_sheet;
	shader = new_shader;
}

void Animation::Animate(float dt)
{
	Shader::UseShader(shader);
	shader.SendUniformVariable("frameX", spriteSheet.frameX);
	shader.SendUniformVariable("frameY", spriteSheet.frameY);
	shader.SendUniformVariable("frameIndex", frameIndex);

	float test = 1.0f / spriteSheet.frameX;
	test;
	frameIndex = int(baseTime) % (spriteSheet.frameX * spriteSheet.frameY);
	baseTime += spriteSheet.animateSpeed * dt;
}

void Animation::ChangeAnimation(int new_count)
{
	spriteSheet.frameX = new_count;
}
