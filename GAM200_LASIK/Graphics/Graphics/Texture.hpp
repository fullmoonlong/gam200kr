/**************************************************************************************
 *	File Name        : Texture.hpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <filesystem>

class Image;
class Color;

class [[nodiscard]] Texture
{
public:
	Texture() = default;
	Texture(Image& image);

	unsigned int GetTexturehandle() const noexcept { return textureHandle; }

	bool LoadTextureFrom(const std::filesystem::path& image_path) noexcept;
	bool LoadTextureFrom(const Image& image) noexcept;
private:
	unsigned int textureHandle;
	
};
