/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: PATH.hpp
 *	
 *	namespace PATH that has all filesystem paths
 *	
 *	2019/11/01
 */

#pragma once
#include <filesystem>

namespace PATH
{
	const std::filesystem::path shape_vert = "../assets/shape.vert";
	const std::filesystem::path shape_frag = "../assets/shape.frag";

	const std::filesystem::path texture_vert = "../assets/texture.vert";
	const std::filesystem::path texture_frag = "../assets/texture.frag";

	const std::filesystem::path sprite_image = "../assets/sprite.png";
}
