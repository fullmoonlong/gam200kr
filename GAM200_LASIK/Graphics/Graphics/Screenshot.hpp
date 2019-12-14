/**************************************************************************************
 *	File Name        : Screenshot.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <vec2.hpp>
#include "Image.hpp"

 /* First parameter is left, bottom position
 Seoncd parameter is size of wanted screenshot size */
Image ScreenShot(int pixels_width, int pixels_height, int left_x = 0, int bottom_y = 0) noexcept;
