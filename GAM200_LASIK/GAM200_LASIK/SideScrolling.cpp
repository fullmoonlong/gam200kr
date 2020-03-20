

#include "Camera.hpp"
#include "EventHandler.hpp"
#include "SideScrolling.h"

SideScrolling::SideScrolling()
	: scrollSpeed(0.0f) {}

void SideScrolling::SetCameraPtr(Camera* camera) {
	cameraPtr = camera;
}

void SideScrolling::SideScroll() {
	cameraPtr->MoveRight(scrollSpeed);
}

void SideScrolling::SideScrollPress(KeyboardButton button) {
	if (button == KeyboardButton::Arrow_Left) {
		scrollSpeed = 5.0f;
	}
	else {
		scrollSpeed = -5.0f;
	}
}


void SideScrolling::SideScrollRelease() {
	scrollSpeed = 0.0f;
}

