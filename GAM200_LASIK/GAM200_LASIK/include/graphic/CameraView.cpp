#include"CameraView.hpp"

glm::mat3 BuildToNDC(CameraView* camera, glm::vec2 size)
{
	switch (camera->GetFrameOfReference())
	{
	case FrameOfReference::RightHanded_OriginCenter:
		return glm::mat3{ camera->GetZoom() * (2.0f / size.x),
					   0.0f,
					   0.0f,
					   0.0f,
					   camera->GetZoom() * (2.0f / size.y),
					   0.0f,
					   0.0f,
					   0.0f,
					   1.0f };
		break;
	case FrameOfReference::RightHanded_OriginBottomLeft:
		return glm::mat3{ camera->GetZoom() * (2.0f / size.x),
					   0.0f,
					   0.0f,
					   0.0f,
					   camera->GetZoom() * (2.0f / size.y),
					   0.0f,
					   -1.0f,
					   -1.0f,
					   1.0f };
		break;
	case FrameOfReference::LeftHanded_OriginTopLeft:
		return glm::mat3{ camera->GetZoom() * (2.0f / size.x),
					   0.0f,
					   0.0f,
					   0.0f,
					   camera->GetZoom() * -(2.0f / size.y),
					   0.0f,
					   -1.0f,
					   1.0f,
					   1.0f };
		break;
	default:
	return glm::mat3{ 1.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,	
	};
	}

}

void CameraView::SetViewSize(glm::vec2 size) noexcept
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