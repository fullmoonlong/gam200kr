#include "Test.hpp"
#include "PATH.hpp"

void Test::Initialize()
{
	if (!window.CanCreateWindow(width, height, this, "Test")) {
		return;
	}
	view.SetViewSize(width, height);

	Shader textureShader;
	textureShader.LoadTextureShader();

	transform.SetScale({ 100.0f });
	const mat3<float>& ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	material.CreateSprite(textureShader, PATH::knight_menu, ndc);
}

void Test::Update()
{
	Draw::StartDrawing();

	Draw::draw(material);

	Draw::FinishDrawing();

	window.PollEvents();
	window.SwapBuffers();
}

void Test::ShutDown()
{
	window.CleanUpWindow();
}

bool Test::IsRunning() const noexcept
{
	return isRunning;
}

void Test::HandleKeyPress(KeyboardButton button)
{
	if (button == KeyboardButton::Escape)
	{
		ShutDown();
	}
}

void Test::HandleWindowClose()
{
	isRunning = false;
}
