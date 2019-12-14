/****************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: VerticesDescriptionLayout.hpp
 *	
 *	Creation Date: Dec.13 2019
 ***************************************************/

#pragma once
#include "VerticesDescription.h"

namespace Layout {
	inline const VerticesDescription& point_color_texturecoordinate() {
		static VerticesDescription layout{
			VerticesDescription::Type::Point,
			VerticesDescription::Type::Color,
			VerticesDescription::Type::TextureCoordinate };
		return layout;
	}
	inline const VerticesDescription& point_color() {
		static VerticesDescription layout{
			VerticesDescription::Type::Point,
			VerticesDescription::Type::Color };
		return layout;
	}
	inline const VerticesDescription& point_texturecoordinate() {
		static VerticesDescription layout{
			VerticesDescription::Type::Point,
			VerticesDescription::Type::TextureCoordinate };
		return layout;
	}
}