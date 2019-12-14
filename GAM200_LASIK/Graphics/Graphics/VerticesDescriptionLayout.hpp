/**************************************************************************************
 *	File Name        : VerticesDescriptionLayout.hpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

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