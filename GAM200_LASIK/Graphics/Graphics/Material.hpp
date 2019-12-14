/**************************************************************************************
 *	File Name        : Material.hpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Texture.hpp"
#include "Animation.hpp"
#include "Color4f.hpp"

struct Material {
	enum class MaterialType {
		Shape,
		Sprite,
		Animation,
		Text
	};
	// This function is for making none moving object.
	void SetMaterials(const MaterialType& material_type, const Shader& new_shader,
		const Mesh& new_mesh, const std::string& texture_path, const mat3<float>& fixed_ndc);
	// This function is for moving object. Use SetNDC function in the update, and then call draw function.
	void SetMaterials(const MaterialType& material_type, const Shader& new_shader, 
		const Mesh& new_mesh, const std::string& texture_path);
	void SetMaterials(const Shader& new_shader, const Vertices& new_vertices,
		const Texture& new_texture, const mat3<float>& new_ndc);
	void CreateShape(const Shader& new_shader, const Mesh& new_mesh, 
		const mat3<float>& new_ndc);
	void CreateSprite(const Shader& new_shader, const Texture& new_texture, 
		const mat3<float>& new_ndc);
	void CreateSprite(const Shader& new_shader, const std::filesystem::path& new_texture_path, 
		const mat3<float>& new_ndc);
	void CreateAnimation(const Shader& new_shader, const Texture& new_sprite_sheet, 
		const Animation& new_animation, const mat3<float>& new_ndc);
	void CreateAnimation(const Shader& new_shader, const std::filesystem::path& new_sprite_sheet_path, 
		const Animation& new_animation, const mat3<float>& new_ndc);
	void CreateText(const Shader& new_shader, const Color4f& new_color, const mat3<float>& new_ndc);
	void SetShader(const Shader& new_shader) { shader = new_shader; }
	void SetVertices(const Vertices& new_vertices) { vertices = new_vertices; }
	void SetTexture(const Texture& new_texture) { texture = new_texture; }
	void SetTexture(const std::filesystem::path& new_texture_path) { texture.LoadTextureFrom(new_texture_path); }
	void SetNDC(const mat3<float>& new_ndc) { ndc = new_ndc; }

	MaterialType materialType;
	Shader shader;
	Vertices vertices;
	mat3<float> ndc;
	Texture texture;
	Animation animation;
	Color4f textColor;
};
