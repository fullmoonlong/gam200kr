

#pragma once

enum class KeyboardButton;
class Camera;

class SideScrolling
{
public:
	SideScrolling();
	void SetCameraPtr(Camera* camera);
	void SideScroll();
	void SideScrollPress(KeyboardButton button);
	void SideScrollRelease();
private:
	Camera* cameraPtr;
	float scrollSpeed;
};

