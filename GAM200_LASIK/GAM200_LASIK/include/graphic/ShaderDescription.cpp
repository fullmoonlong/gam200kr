/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: ShaderDescription.cpp
*	
*	Shader description
*	
*	2019/10/04
*/

#include <GL/glew.h>
#include <graphic/ShaderDescription.h>

void ShaderDescription::AddType(Type type) noexcept
{
	TypeDescription description;
	if (type == Point)
	{
		description.elementsType = GL_FLOAT;
		description.elementsNumber = 2;
		description.sizeInBytes = description.elementsNumber * sizeof(float);
		description.shouldNormalize = false;
	}
	if (type == TextCoordinate)
	{
		description.elementsType = GL_FLOAT;
		description.elementsNumber = 2;
		description.sizeInBytes = description.elementsNumber * sizeof(float);
		description.shouldNormalize = false;
	}
	if (type == Color)
	{
		description.elementsType = GL_FLOAT;
		description.elementsNumber = 4;
		description.sizeInBytes = description.elementsNumber * sizeof(float);
		description.shouldNormalize = false;
	}
	types.push_back(type);
	typeDescription.push_back(description);
	vertexSize += description.sizeInBytes;
}

const std::vector<ShaderDescription::Type>& ShaderDescription::GetTypes() const noexcept
{
	return types;
}

ShaderDescription::ShaderDescription(std::initializer_list<Type> fields) noexcept
{
	for (Type element : fields)
	{
		AddType(element);
	}
}

unsigned ShaderDescription::GetVertexSize() const noexcept
{
	return vertexSize;
}

void ShaderDescription::EnableAttributes() const noexcept
{
	const int index = (int)(typeDescription.size());
	uintptr_t offset = 0;
	for (int i = 0; i < index; i++)
	{
		TypeDescription description = typeDescription[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, description.elementsNumber, description.elementsType, description.shouldNormalize, vertexSize, (GLvoid*)offset);
		offset += description.sizeInBytes;
	}
}
