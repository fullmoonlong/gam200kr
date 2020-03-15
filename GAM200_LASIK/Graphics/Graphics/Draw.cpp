/**************************************************************************************
 *	File Name        : Draw.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <GL/glew.h>
#include "Draw.hpp"
#include "../GAM200_LASIK/Object.h"

void Draw::StartDrawing()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Background will be cleared with parameter */
void Draw::StartDrawing(const Color4f& background_color)
{
	glClearColor(background_color.r, background_color.g, background_color.b, background_color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Draw::FinishDrawing()
{
	glFinish();
}

void Draw::draw(Material& material)
{
	glBindTexture(GL_TEXTURE_2D, material.texture.GetTexturehandle());
	material.shader.Use();
	material.shader.SendUniformVariable("ndc", material.ndc);
	Vertices::SelectVAO(material.vertices);
	glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
}

void Draw::DrawShape(Material& material)
{
	material.shader.Use();
	material.shader.SendUniformVariable("ndc", material.ndc);
	Vertices::SelectVAO(material.vertices);
	glDrawArrays(material.vertices.GetPattern(), 0, material.vertices.GetVerticesCount());
}

void Draw::DrawText(const Shader& shader, const mat3<float>& ndc, const Text& text)
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
		draw(textMaterial);
	}
}


Renderer::Renderer() noexcept {
	shapeShader.LoadShapeShader();
	spriteShader.LoadTextureShader();
	animationShader.LoadAnimationShader();
	//textShader.LoadTextShader();
}

//void Renderer::Draw(Object* object) {
//	Material* material = &object->material;
//	object->texture.Bind();
//	Shader::Use(material->shader);
//	material->shader.SendUniformVariable("ndc", material->ndc);
//	Vertices::SelectVAO(material->vertices);
//	glDrawArrays(material->vertices.GetPattern(), 0, material->vertices.GetVerticesCount());
//}

//void Renderer::Draw(const mat3<float>& ndc, const Text& text) {
//	for (const auto& vertices_texture : text.GetPairOfVerticesAndTextures()) {
//		const Vertices& textVertices = *vertices_texture.first;
//		const Texture*  textTexture  = vertices_texture.second;
//		Material textMaterial;
//		textMaterial.CreateText(textShader, { 1.0f }, ndc);
//		textShader.SendUniformVariable("textColor", { 1.0f });
//		textMaterial.SetVertices(textVertices);
//		textMaterial.SetTexture(*textTexture);
//		draw(textMaterial);
//	}
//}
