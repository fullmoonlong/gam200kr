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

class Mesh;

class [[nodiscard]] Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	bool LoadShader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	void InitializeWithMesh(const Mesh& mesh) noexcept;
	unsigned GetHandleToShader() const noexcept;
	unsigned int VBO = 0, VAO = 0;
private:
	unsigned handleToShader = 0;
};

