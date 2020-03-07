/**************************************************************************************
 *	File Name        : Graphic.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019~2020 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#pragma once
#include <map>
#include <vector>
#include "System.h"
#include "OpenGLWindow.hpp"

#include "Camera.hpp"
#include "CameraView.hpp"

#include "Mesh.h"
#include "Draw.hpp"
#include "Shader.h"
#include "Image.hpp"
#include "Object.h"
#include "Vertices.h"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Animation.hpp"


class Graphic : public System
{
public:
	Graphic(OpenGLWindow* window);
	~Graphic();
	void Initialize() override;
	void Update(float dt) override;

	void AddMaterialAndTransform(Material* material, Transform* transform);
	void AddMaterialAndTransform(Material* material, Transform* transform, Animation* animation);
	void AddText(Text* text, Transform* transform);
	void SetBackground(std::filesystem::path image, float width, float height);

	void DeleteMaterial(Material* material);
	void DeleteText(Text* text);

	void DeleteAllObjectGraphic();
	void DeleteAllText();
	void DeleteAllGraphicList();
	void ResetGraphic();

	Camera camera;
	CameraView view;

	mat3<float> cameraToNDC;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;

	Draw draw;

	Mesh mesh; 
	Mesh backgroundMesh;	

	Color4f color { 1.0f, 1.0f, 1.0f, 1.0f };
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };

	Shader shader;
	Shader shapeShader;
	Shader fontShader;
	Shader backgroundShader;

	Object background;
	Material* backgroundMaterial;
	Transform* backgroundTransform;

	std::map<int, Material*> materials;
	std::map<int, Transform*> materialTransforms;
	std::map<int, Animation*> animations;

	std::map<int, Text*> texts;
	std::map<int, Transform*> textTransforms;

	int materialID = 0;
	int textID = 0;
	bool isBackgroundOn = false;

	OpenGLWindow* windowPoint;
};
extern Graphic* GRAPHIC;