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

void Material::CreateShape(const Shader& new_shader, const Mesh& new_mesh,
	const mat3<float>& new_ndc)
{
	materialType = MaterialType::Shape;
	this->shader = new_shader;
	this->vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_color());
	this->ndc = new_ndc;
}

void Material::CreateSprite(const Shader& new_shader, const Texture& new_texture, 
	const mat3<float>& new_ndc)
{
	materialType = MaterialType::Sprite;
	this->shader = new_shader;
	this->vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(),
		Layout::point_texturecoordinate());
	this->texture = new_texture;
	this->ndc = new_ndc;
}

void Material::CreateSprite(const Shader& new_shader, const std::filesystem::path& new_texture_path, 
	const mat3<float>& new_ndc)
{
	materialType = MaterialType::Sprite;
	this->shader = new_shader;
	this->vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(), 
		Layout::point_texturecoordinate());
	this->texture.LoadTextureFrom(new_texture_path);
	this->ndc = new_ndc;
}

void Material::CreateAnimation(const Shader& new_shader, const Texture& new_sprite_sheet, 
	const Animation& new_animation, const mat3<float>& new_ndc)
{
	materialType = MaterialType::Animation;
	this->shader = new_shader;
	this->vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(),
		Layout::point_texturecoordinate());
	this->texture = new_sprite_sheet;
	this->animation = new_animation;
	this->ndc = new_ndc;
}

void Material::CreateAnimation(const Shader& new_shader, const std::filesystem::path& new_sprite_sheet_path, 
	const Animation& new_animation, const mat3<float>& new_ndc)
{
	materialType = MaterialType::Animation;
	this->shader = new_shader;
	this->vertices.InitializeWithMeshAndLayout(MESH::create_sprite_box(),
		Layout::point_texturecoordinate());
	this->texture.LoadTextureFrom(new_sprite_sheet_path);
	this->animation = new_animation;
	this->ndc = new_ndc;
}

void Material::CreateText(const Shader& new_shader, const Color4f& new_text_color, const mat3<float>& new_ndc)
{
	materialType = MaterialType::Animation;
	this->shader = new_shader;
	this->textColor = new_text_color;
	this->ndc = new_ndc;
}
