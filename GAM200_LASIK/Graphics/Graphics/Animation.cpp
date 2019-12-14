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

void Animation::Initialize(SpriteSheet new_sprite_sheet, const Shader& new_shader)
{
	this->shader = new_shader;
	this->spriteSheet = new_sprite_sheet;
}

void Animation::Initialize(int column, int row, float animation_speed, const Shader& new_shader)
{
	this->shader = new_shader;
	spriteSheet = { column, row, animation_speed };
}

void Animation::Animate(float dt)
{
	Shader::UseShader(shader);
	shader.SendUniformVariable("frameX", spriteSheet.frameX);
	shader.SendUniformVariable("frameY", spriteSheet.frameY);
	shader.SendUniformVariable("frameIndex", frameIndex);

	frameIndex = int(baseTime) % (spriteSheet.frameX * spriteSheet.frameY);
	baseTime += spriteSheet.animateSpeed * dt;
}

void Animation::ChangeAnimation(SpriteSheet new_sprite_sheet)
{
	spriteSheet = new_sprite_sheet;
}

void Animation::ChangeAnimation(int new_column, int new_row)
{
	spriteSheet.frameX = new_column;
	spriteSheet.frameY = new_row;
}

void Animation::ChangeAnimation(int new_column, int new_row, float new_animation_speed)
{
	spriteSheet = { new_column, new_row, new_animation_speed };
}
