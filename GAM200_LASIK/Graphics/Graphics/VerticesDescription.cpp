/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: VerticesDescription.cpp
 *	
 *	Vertices description
 *	
 *	2019/10/31
 */

#include "GL/glew.h"
#include "VerticesDescription.h"

void VerticesDescription::AddType(Type type) noexcept
{
	TypeDescription description;
	if (type == Type::Point)
	{
		description.elementsType = GL_FLOAT;
		description.elementsNumber = 2;
		description.sizeInBytes = description.elementsNumber * sizeof(float);
		description.shouldNormalize = false;
	}
	if (type == Type::TextureCoordinate)
	{
		description.elementsType = GL_FLOAT;
		description.elementsNumber = 2;
		description.sizeInBytes = description.elementsNumber * sizeof(float);
		description.shouldNormalize = false;
	}
	if (type == Type::Color)
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

const std::vector<VerticesDescription::Type>& VerticesDescription::GetTypes() const noexcept
{
	return types;
}

VerticesDescription::VerticesDescription(std::initializer_list<Type> fields) noexcept
{
	for (Type element : fields)
	{
		AddType(element);
	}
}

unsigned VerticesDescription::GetVertexSize() const noexcept
{
	return vertexSize;
}

void VerticesDescription::EnableAttributes() const noexcept
{
	const int index = (int)typeDescription.size();
	uintptr_t offset = 0;
	for (int i = 0; i < index; ++i)
	{
		TypeDescription description = typeDescription[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, description.elementsNumber, description.elementsType, description.shouldNormalize, vertexSize, (GLvoid*)offset);
		offset += description.sizeInBytes;
	}
}
