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

	const std::filesystem::path skeleton_move = "../assets/skeleton_move.png";
	const std::filesystem::path skeleton_attack = "../assets/skeleton_attack.png";

	const std::filesystem::path golem_move = "../assets/golem_move.png";
	const std::filesystem::path golem_attack = "../assets/golem_attack.png";

	const std::filesystem::path lich_move = "../assets/lich_move.png";
	const std::filesystem::path lich_attack = "../assets/lich_attack.png";

	const std::filesystem::path knight_move = "../assets/knight_move.png";
	const std::filesystem::path knight_attack = "../assets/knight_attack.png";
	const std::filesystem::path knight_menu = "../assets/knight.png";

	const std::filesystem::path magician_move = "../assets/magician_move.png";
	const std::filesystem::path magician_attack = "../assets/magician_attack.png";
	const std::filesystem::path magician_menu = "../assets/magician.png";

	const std::filesystem::path archer_move = "../assets/archer_move.png";
	const std::filesystem::path archer_attack = "../assets/archer_attack.png";
	const std::filesystem::path archer_menu = "../assets/archer.png";

	const std::filesystem::path arrow = "../assets/arrow.png";
	const std::filesystem::path fireball = "../assets/fireball.png";
	const std::filesystem::path tower = "../assets/tower.png";
	const std::filesystem::path lair = "../assets/lair.png";
	const std::filesystem::path hpBar = "../assets/hpBar.png";
	const std::filesystem::path twocountdown = "../assets/twocountdown.png";
	const std::filesystem::path threecountdown = "../assets/threecountdown.png";
	const std::filesystem::path fourcountdown = "../assets/fourcountdown.png";

	const std::filesystem::path icon_image = "../assets/icon.png";

	const std::filesystem::path bitmapfont_fnt = "../assets/bitmapfont.fnt";
	const std::filesystem::path bitmapfont_png = "../assets/bitmapfont_0.png";

	const std::filesystem::path background = "../assets/background.jpg";
}
