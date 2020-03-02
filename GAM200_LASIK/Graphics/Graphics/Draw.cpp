/**************************************************************************************
 *	File Name        : Drawing.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <GL/glew.h>
#include "Draw.hpp"

void Drawing::StartDrawing()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Background will be cleared with parameter */
void Drawing::StartDrawing(const Color4f& background_color)
{
	glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Drawing::FinishDrawing()
{
	glFinish();
}

//void Drawing::Draw(const Material& material)
//{
//	glBindTexture(GL_TEXTURE_2D, material.texture.GetTexturehandle());
//	Shader::UseShader(material.shader);
//	material.shader.SendUniformVariable("ndc", material.ndc);
//	Vertices::SelectVAO(material.vertices);
//	glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
//}

void Drawing::Draw(const Material& material)
{
	switch (material.materialType) {
	case Material::MaterialType::Shape:
		Shader::UseShader(material.shader);
		material.shader.SendUniformVariable("ndc", material.ndc);
		Vertices::SelectVAO(material.vertices);
		glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
		break;
	case Material::MaterialType::Animation:
	case Material::MaterialType::Sprite:
		glBindTexture(GL_TEXTURE_2D, material.texture.GetTexturehandle());
		Shader::UseShader(material.shader);
		material.shader.SendUniformVariable("ndc", material.ndc);
		Vertices::SelectVAO(material.vertices);
		glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
		break;
	//case Material::MaterialType::Text:
	//	break;
	default:
		glBindTexture(GL_TEXTURE_2D, material.texture.GetTexturehandle());
		Shader::UseShader(material.shader);
		material.shader.SendUniformVariable("ndc", material.ndc);
		Vertices::SelectVAO(material.vertices);
		glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
		break;
	}
}

void Drawing::DrawShape(const Material& material)
{
	Shader::UseShader(material.shader);
	material.shader.SendUniformVariable("ndc", material.ndc);
	Vertices::SelectVAO(material.vertices);
	glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
}

void Drawing::DrawText(const Shader& shader, const mat3<float>& ndc, const Text& text)
{
	for (const auto& vertices_texture : text.GetPairOfVerticesAndTextures())
	{
		const Vertices& textVertices = *vertices_texture.first;
		const Texture*  textTexture  = vertices_texture.second;
		Material textMaterial;
		textMaterial.CreateText(shader, { 1.0f }, ndc);
		shader.SendUniformVariable("textColor", { 1.0f });
		textMaterial.SetVertices(textVertices);
		textMaterial.SetTexture(*textTexture);
		Draw(textMaterial);
	}
}
