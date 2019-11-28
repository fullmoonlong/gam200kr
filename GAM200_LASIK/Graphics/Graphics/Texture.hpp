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
#include <filesystem>

class Image;
class Color;

class [[nodiscard]] Texture
{
public:
	Texture() = default;
	Texture(Image& image);

	unsigned int GetTexturehandle() const noexcept { return textureHandle; }

	bool LoadFromPath(const std::filesystem::path& image_path) noexcept;
	bool LoadFromImage(const Image& image) noexcept;
	bool LoadBackground() noexcept;
private:
	unsigned int textureHandle;
	
};
