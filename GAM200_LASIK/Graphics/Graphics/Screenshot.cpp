/**************************************************************************************
 *	File Name        : Screenshot.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Screenshot.hpp"
#include <GL/glew.h>

Image ScreenShot(int pixels_width, int pixels_height, int left_x, int bottom_y) noexcept
{
	Image screenshot;
	glReadBuffer(GL_BACK);
	screenshot.ResizePixelSize(pixels_width, pixels_height);
	if (glReadnPixels != nullptr)
	{
		glReadnPixels(left_x, bottom_y, pixels_width, pixels_height, GL_RGBA, GL_UNSIGNED_BYTE, screenshot.GetPixelsBufferBytesSize(), screenshot.GetPixelPointer());
	}
	else
	{
		glReadPixels(left_x, bottom_y, pixels_width, pixels_height, GL_RGBA, GL_UNSIGNED_BYTE, screenshot.GetPixelPointer());
	}
	screenshot.FlipVertically();

	return screenshot;
}
