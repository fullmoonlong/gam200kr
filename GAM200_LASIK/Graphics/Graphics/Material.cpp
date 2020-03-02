/**************************************************************************************
 *	File Name        : Material.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Mesh.h"
#include "Material.hpp"
#include "VerticesDescriptionLayout.hpp"

void Material::CreateShape(const Shader& new_shader,
	const Mesh& new_mesh,
	const vec2<float>& size,
	const vec2<float>& position) {
	materialType = MaterialType::Shape;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_color());
	transform.SetScale(size);
	transform.SetTranslation(position);
}

void Material::CreateShape(const Shader& new_shader, const Mesh& new_mesh,
	const mat3<float>& new_ndc)
{
	materialType = MaterialType::Shape;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_color());
	ndc = new_ndc;
}

void Material::CreateSprite(const Shader& new_shader, const Texture& new_texture, 
	const mat3<float>& new_ndc)
{
	materialType = MaterialType::Sprite;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(),
		Layout::point_texturecoordinate());
	texture = new_texture;
	ndc = new_ndc;
}

void Material::CreateSprite(const Shader& new_shader, const std::filesystem::path& new_texture_path, 
	const mat3<float>& new_ndc)
{
	materialType = MaterialType::Sprite;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(), 
		Layout::point_texturecoordinate());
	texture.LoadTextureFrom(new_texture_path);
	ndc = new_ndc;
}

void Material::CreateSprite(const Shader& new_shader, const std::string& file_name, const vec2<float>& size,
	const vec2<float>& position) {
	materialType = MaterialType::Sprite;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(), Layout::point_texturecoordinate());
	texture.LoadTextureFrom(file_name);
	transform.SetScale(size);
	transform.SetTranslation(position);
}

void Material::CreateAnimation(const Shader& new_shader, const Texture& new_sprite_sheet, 
	const Animation& new_animation, const mat3<float>& new_ndc)
{
	materialType = MaterialType::Animation;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(),
		Layout::point_texturecoordinate());
	texture = new_sprite_sheet;
	animation = new_animation;
	ndc = new_ndc;
}

void Material::CreateAnimation(const Shader& new_shader, const std::filesystem::path& new_sprite_sheet_path, 
	const Animation& new_animation, const mat3<float>& new_ndc)
{
	materialType = MaterialType::Animation;
	shader = new_shader;
	vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(),
		Layout::point_texturecoordinate());
	texture.LoadTextureFrom(new_sprite_sheet_path);
	animation = new_animation;
	ndc = new_ndc;
}

void Material::CreateText(const Shader& new_shader, const Color4f& new_text_color, const mat3<float>& new_ndc)
{
	materialType = MaterialType::Animation;
	shader = new_shader;
	textColor = new_text_color;
	ndc = new_ndc;
}
