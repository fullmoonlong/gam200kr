/****************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Material.hpp
 *	
 *	Creation Date: Dec.14 2019
 ***************************************************/

#pragma once
#include "Shader.h"
#include "Vertices.h"
#include "Texture.hpp"

struct Material {
	enum class MaterialType {
		Shape,
		Sprite,
		Animation,
		Text
	};
	void SetMaterials(const MaterialType& material_type, const Shader& new_shader,
		const Mesh& new_mesh, const std::string& texture_path, const mat3<float>& new_ndc);
	void SetMaterials(const Shader& new_shader, const Vertices& new_vertices,
		const Texture& new_texture, const mat3<float>& new_ndc);
	void SetShader(const Shader& new_shader) { shader = new_shader; }
	void SetVertices(const Vertices& new_vertices) { vertices = new_vertices; }
	void SetTexture(const Texture& new_texture) { texture = new_texture; }
	void SetNDC(const mat3<float>& new_ndc) { ndc = new_ndc; }

	Shader shader;
	Vertices vertices;
	mat3<float> ndc;
	Texture texture;
};
