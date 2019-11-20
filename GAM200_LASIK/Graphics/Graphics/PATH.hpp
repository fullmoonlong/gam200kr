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
	const std::filesystem::path animation_vert = "../assets/animation.vert";
	const std::filesystem::path animation_frag = "../assets/animation.frag";
	
	const std::filesystem::path shape_vert = "../assets/shape.vert";
	const std::filesystem::path shape_frag = "../assets/shape.frag";

	const std::filesystem::path texture_vert = "../assets/texture.vert";
	const std::filesystem::path texture_frag = "../assets/texture.frag";

	const std::filesystem::path kevin_move   = "../assets/kevin_move.png";
	const std::filesystem::path kevin_attack = "../assets/kevin_attack.png";

	const std::filesystem::path knight_move = "../assets/knight_move.png";
	const std::filesystem::path knight_attack = "../assets/knight_attack.png";

	const std::filesystem::path wizard_move = "../assets/wizard_move.png";
	const std::filesystem::path wizard_attack = "../assets/wizard_attack.png";

	const std::filesystem::path archer_move = "../assets/archer_move.png";
	const std::filesystem::path archer_attack = "../assets/archer_attack.png";

	const std::filesystem::path arrow = "../assets/arrow.png";
	const std::filesystem::path fireball = "../assets/fireball.png";

	const std::filesystem::path icon_image = "../assets/icon.png";

	const std::filesystem::path bitmapfont_fnt = "../assets/bitmapfont.fnt";
	const std::filesystem::path bitmapfont_png = "../assets/bitmapfont_0.png";

	const std::filesystem::path background = "../assets/background.jpg";
}
