#pragma once
#include <glm.hpp>

enum FrameOfReference
{
	RightHanded_OriginCenter,
	RightHanded_OriginBottomLeft,
	LeftHanded_OriginTopLeft,
	Normalize
};

class [[nodiscard]] CameraView
{
public:
	glm::mat3         GetCameraToNDCTransform() const noexcept { return cameraToNDC; }
	void                       SetFrameOfReference(FrameOfReference frame_of_reference) noexcept;
	constexpr FrameOfReference GetFrameOfReference() const noexcept { return frameOfReference; }

	void            SetViewSize(glm::vec2 size) noexcept;
	void            SetViewSize(int pixel_width, int pixel_height) noexcept;
	void            SetZoom(float new_zoom) noexcept;
	constexpr float GetZoom() const noexcept { return zoom; }

private:
	glm::vec2 displaySize;
	glm::mat3 cameraToNDC = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	float zoom{1.0f};
	FrameOfReference frameOfReference = FrameOfReference::RightHanded_OriginCenter;
};