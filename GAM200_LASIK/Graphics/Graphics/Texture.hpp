/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Texture.hpp
*	
*	Texture of the sprite
*	
*	2019/10/07
*/

#pragma once

class Image;
class Color;

class [[nodiscard]]Texture
{
public:
	Texture() = default;

	unsigned int GetTexturehandle() const noexcept { return textureHandle; }

	bool LoadTextureFrom(const Image& image) noexcept;
	
private:
	unsigned int textureHandle;
	
};

