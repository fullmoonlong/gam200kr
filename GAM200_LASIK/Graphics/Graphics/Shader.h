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
#include <filesystem>
#include "mat3.hpp"

class [[nodiscard]] Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::filesystem::path& vertex_source,
		const std::filesystem::path& fragment_source) noexcept;
	bool LoadShaderFrom(const std::filesystem::path& vertex_source,
		const std::filesystem::path& fragment_source) noexcept;
	unsigned GetHandleToShader() const noexcept;

	void SendUniformVariable(const char* variable_name, const int& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const float& variable) const noexcept;
	void SendUniformVariable(const char* variable_name, const mat3<float>& matrix) const noexcept;
private:
	unsigned int handleToShader = 0;
};

