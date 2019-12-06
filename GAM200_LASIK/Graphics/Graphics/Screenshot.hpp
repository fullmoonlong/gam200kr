/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Screenshot.hpp
 *	
 *	Screenshot the window
 *	
 *	Dec.05 2019
 */

#pragma once
#include <vec2.hpp>
#include "Image.hpp"

 /* First parameter is left, bottom position
 Seoncd parameter is size of wanted screenshot size */
Image ScreenShot(int pixels_width, int pixels_height, int left_x = 0, int bottom_y = 0) noexcept;
