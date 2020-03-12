/**************************************************************************************
 *	File Name        : Graphic.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019~2020 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include "Graphic.h"
#include "PATH.hpp"

extern Graphic* GRAPHIC = nullptr;
Graphic::Graphic(OpenGLWindow* window)
{
	GRAPHIC = this;
	windowPoint = window;
}

Graphic::~Graphic()
{
	ResetGraphic();
}

void Graphic::Initialize()
{
	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);
	fontShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	shapeShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	backgroundShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	const Mesh mesh_ = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);
	mesh = mesh_;

	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);
	cameraToNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera();

}

void Graphic::Update(float dt)
{
	camera.Rotate(cameraAngle);
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);
	cameraToNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera();

	Draw::StartDrawing();
	if (isBackgroundOn == true)
	{
		mat3<float> backgroundNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * background.transform.GetModelToWorld();
		background.material.ndc = backgroundNDC;
		Draw::draw(background.material);
	}

	if (!materials.empty())
	{
		for (auto material : materials)
		{
			if (material.second != nullptr)
			{
				if (animations[material.first] != nullptr)
				{
					animations[material.first]->Animate(dt);
				}
				material.second->ndc = cameraToNDC * materialTransforms[material.first]->GetModelToWorld();;
				Draw::draw(*material.second);
			}
		}
	}

	if (!texts.empty())
	{
		for (auto text : texts)
		{
			const mat3<float> textNDC = cameraToNDC * textTransforms[text.first]->GetModelToWorld();
			Draw::DrawText(fontShader, textNDC, *text.second);
		}
	}
	Draw::FinishDrawing();
}

void Graphic::AddMaterialAndTransform(Material* material, Transform* transform)
{
	materials[materialID] = material;
	materialTransforms[materialID] = transform;
	materialID++;
}

void Graphic::AddMaterialAndTransform(Material* material, Transform* transform, Animation* animation)
{
	materials[materialID] = material;
	materialTransforms[materialID] = transform;
	animations[materialID] = animation;
	materialID++;
}

void Graphic::AddText(Text* text, Transform* transform)
{
	texts[textID] = text;
	textTransforms[textID] = transform;
	textID++;
}

void Graphic::SetBackground(std::filesystem::path image, float width, float height)
{
	background.material.vertices.InitializeWithMeshAndLayout(mesh, layout);
	backgroundMesh.SetShapePattern(ShapePattern::TriangleFan);
	background.material.texture.LoadTextureFrom(image);
	background.material.CreateSprite(backgroundShader, background.material.texture, background.material.ndc);
	vec2<float> scale{ width, height };
	background.transform.SetScale(scale);
	isBackgroundOn = true;
}

void Graphic::DeleteMaterial(Material* material)
{
	for (int i = 0; i < materials.size(); i++)
	{
		if (materials[i] != nullptr && materials[i] == material)
		{
			materials.erase(i);
			materialTransforms.erase(i);
			if (animations[i] != nullptr)
			{
				animations.erase(i);
			}
			break;
		}
	}
}

void Graphic::DeleteText(Text* text)
{
	for (int i = 0; i < texts.size(); i++)
	{
		if (texts[i] == text)
		{
			texts.erase(i);
			textTransforms.erase(i);
			break;
		}
	}
}

void Graphic::DeleteAllObjectGraphic()
{
	materials.clear();
	materialTransforms.clear();
	animations.clear();
	materialID = 0;
}

void Graphic::DeleteAllText()
{
	texts.clear();
	textTransforms.clear();
	textID = 0;
}

void Graphic::DeleteAllGraphicList()
{
	DeleteAllObjectGraphic();
	DeleteAllText();

	isBackgroundOn = false;
}

void Graphic::ResetGraphic()
{
	DeleteAllGraphicList();
	zoom = 0.f;
	cameraAngle = 0.0f;
}
