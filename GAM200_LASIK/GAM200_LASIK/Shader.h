#pragma once
#include <string>

class Shader
{
public:
	Shader() noexcept = default;
	Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code) noexcept;
	bool LoadShader(const std::string& vertex_source, const std::string& fragment_source) noexcept;
	unsigned GetHandleToShader();
	unsigned int VBO, VAO;
private:
	unsigned handleToShader = 0;
};

