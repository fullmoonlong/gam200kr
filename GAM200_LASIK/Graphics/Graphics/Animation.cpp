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

//animation.spriteCount = spriteCount;
//float oneSide = 1.f / (float)animation.spriteCount;
//for (int i = 0; i <= animation.spriteCount; ++i)
//{
//	animation.texCoord.push_back((float)i * oneSide);
//}
//Image image;
//image.LoadFrom(sprite_image);
//animation.sprite.LoadTextureFrom(image);
//animation.baseTime = 0;


//static int spriteIndex = 0;
//animation.baseTime += dt;
//
//float texCoord[] = {
//	animation.texCoord.at(spriteIndex), 0.f,
//	animation.texCoord.at(spriteIndex + 1), 0.f,
//	animation.texCoord.at(spriteIndex + 1), 1.f,
//	animation.texCoord.at(spriteIndex), 1.f
//};
//
//glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);
//
//if (animation.baseTime >= 0.125f)
//{
//	spriteIndex++;
//	if (spriteIndex == 8)
//	{
//		spriteIndex = 0;
//	}
//	animation.baseTime -= 0.125f;
//}

void Animation::Initialize(Image& new_sprite, Mesh& new_shape, int new_count)
{
	spriteSheet.LoadTextureFrom(new_sprite);
	shape = new_shape;
	sceneCount = new_count;
	float oneSide = 1.0f / (float)sceneCount;
	for (int i = 0; i <= sceneCount; ++i)
	{
		textureCoord.push_back((float)i * oneSide);
	}
}

Animation::Animation(Image& new_sprite, Mesh& new_shape, int new_count)
{
	Initialize(new_sprite, new_shape, new_count);
}

void Animation::Animate(float dt)
{
	static int spriteIndex = 0;
	baseTime += dt;
	
	float texCoord[] = {
		textureCoord.at(spriteIndex), 0.0f,
		textureCoord.at(spriteIndex), 1.0f,
		textureCoord.at(spriteIndex + 1), 1.0f,
		textureCoord.at(spriteIndex + 1), 0.0f,
	};
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);
	//glBindTexture(GL_TEXTURE_2D, spriteSheet.GetTexturehandle());
	
	if (baseTime >= 0.125f)
	{
		spriteIndex++;
		if (spriteIndex == 8)
		{
			spriteIndex = 0;
		}
		baseTime -= 0.125f;
	}
}
