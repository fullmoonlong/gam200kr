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

	material.shader.LoadTextureShader();
	//material.vertices.InitializeWithMeshAndLayout(mesh, layout);
	//material.texture.LoadFromPath(PATH::knight_menu);
	transform.SetScale({ 100.0f });
	const mat3<float>& ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	material.CreateSprite(textureShader, PATH::knight_menu, ndc);
}

void Test::Update()
{
	Drawing::StartDrawing();

	Drawing::Draw(material);

	Drawing::FinishDrawing();

	window.PollEvents();
	window.SwapBuffers();
}

void Test::ShutDown()
{
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
