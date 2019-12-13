/****************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Material.cpp
 *	
 *	Creation Date: Dec.14 2019
 ***************************************************/

#include "Material.hpp"
#include "VerticesDescriptionLayout.hpp"

void Material::SetMaterials(const MaterialType& material_type, const Shader& new_shader, const Mesh& new_mesh,
	const std::string& texture_path, const mat3<float>& new_ndc) {
	switch (material_type) {
	case Material::MaterialType::Shape:
		shader = new_shader;
		vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_color());
		ndc = new_ndc;
		break;
	case Material::MaterialType::Sprite:
		shader = new_shader;
		vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_texturecoordinate());
		texture.LoadTextureFrom(texture_path);
		ndc = new_ndc;
		break;
	case Material::MaterialType::Animation:
		shader = new_shader;
		vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_texturecoordinate());
		texture.LoadTextureFrom(texture_path);
		ndc = new_ndc;
		break;
	case Material::MaterialType::Text:	// fix
		shader = new_shader;
		vertices.InitializeWithMeshAndLayout(new_mesh, Layout::point_texturecoordinate());
		texture.LoadTextureFrom(texture_path);
		ndc = new_ndc;
	}
}

void Material::SetMaterials(const Shader& new_shader, const Vertices& new_vertices, const Texture& new_texture,
	const mat3<float>& new_ndc) {
	
}
