/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Shader.h
*	
*	Implementing shader
*	
*	2019/09/25
*/

#pragma once
#include <string>
#include "ShaderDescription.h"
#include <mat3.hpp>

class Mesh;

class [[nodiscard]] Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	bool LoadShader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	void InitializeWithMesh(const Mesh& mesh, const ShaderDescription& shader_layout) noexcept;
	unsigned GetHandleToShader() const noexcept;

	void SendUniformVariable(const char* variable_name, const int& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const float& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const Math::mat3<float>& variable) const noexcept;
	
	unsigned int VBO = 0;
	unsigned int VAO = 0;
private:
	void WriteMeshDataToVertexBuffer(const Mesh& mesh) const noexcept;

	int verticesCount = 0;
	int bufferVertexCapacity = 0;
	unsigned int handleToShader = 0;
	unsigned int pattern = 0;
	ShaderDescription layout{};
};

