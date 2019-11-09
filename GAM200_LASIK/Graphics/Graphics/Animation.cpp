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

void Animation::Initialize(Image& new_sprite, Mesh& new_shape, int new_count)
{
	glGenBuffers(1, &textureCoordinateBuffer);
	spriteSheet.LoadTextureFrom(new_sprite);
	shape = new_shape;
	sceneCount = new_count;
	float oneSide = 1.0f / (float)sceneCount;
	const float correction = 0.0005f * sceneCount;	//this number hide the texture coordinate error
	for (int i = 0; i <= sceneCount; ++i)
	{
		textureCoord.push_back((float)i * oneSide - correction);
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
	
	glBindBuffer(GL_ARRAY_BUFFER, textureCoordinateBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_DYNAMIC_DRAW);
	//glBindTexture(GL_TEXTURE_2D, spriteSheet.GetTexturehandle());
	
	if (baseTime >= 0.125f)
	{
		spriteIndex++;
		if (spriteIndex == sceneCount)
		{
			spriteIndex = 0;
		}
		baseTime -= 0.125f;
	}
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
}

void Animation::ChangeAnimation(const std::filesystem::path& new_sprite, int new_count)
{
	spriteSheet.LoadTextureFrom(new_sprite);
	textureCoord.clear();
	sceneCount = new_count;
	float oneSide = 1.0f / (float)sceneCount;
	const float correction = 0.0005f * sceneCount;	//this number hide the texture coordinate error
	for (int i = 0; i <= sceneCount; ++i)
	{
		textureCoord.push_back((float)i * oneSide - correction);
	}
}
