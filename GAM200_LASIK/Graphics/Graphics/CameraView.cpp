/**************************************************************************************
 *	File Name        : CameraView.cpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "CameraView.hpp"

mat3<float> BuildToNDC(CameraView* camera, vec2<float> windowSize)
{
	switch (camera->GetFrameOfReference())
	{
	case FrameOfReference::RightHanded_OriginCenter:
		return mat3<float>{
			camera->GetZoom() * (2.0f / windowSize.x), 0.0f, 0.0f,
			0.0f, camera->GetZoom() * (2.0f / windowSize.y), 0.0f,
			0.0f, 0.0f, 1.0f };
	case FrameOfReference::RightHanded_OriginBottomLeft:
		return mat3<float>{
			camera->GetZoom() * (2.0f / windowSize.x), 0.0f, 0.0f,
			0.0f, camera->GetZoom() * (2.0f / windowSize.y), 0.0f,
			-1.0f, -1.0f, 1.0f };
	case FrameOfReference::LeftHanded_OriginTopLeft:
		return mat3<float>{
			camera->GetZoom() * (2.0f / windowSize.x), 0.0f, 0.0f,
			0.0f, camera->GetZoom() * -(2.0f / windowSize.y), 0.0f,
			-1.0f, 1.0f, 1.0f };
	default:
	return mat3<float>{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f };
	}
}

void CameraView::SetViewSize(vec2<float> size) noexcept
{
	displaySize = size;
	cameraToNDC = BuildToNDC(this, displaySize);
}

void CameraView::SetViewSize(int pixel_width, int pixel_height) noexcept
{
	displaySize.x = static_cast<float>(pixel_width);
	displaySize.y = static_cast<float>(pixel_height);
	cameraToNDC = BuildToNDC(this, displaySize);
}

void CameraView::SetZoom(float new_zoom) noexcept
{
	zoom = new_zoom;
	cameraToNDC = BuildToNDC(this, displaySize);
}

void CameraView::SetFrameOfReference(FrameOfReference frame_of_reference) noexcept
{
	frameOfReference = frame_of_reference;
	cameraToNDC = BuildToNDC(this, displaySize);
}