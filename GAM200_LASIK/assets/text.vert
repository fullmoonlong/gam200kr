/**************************************************************************************
 *	File Name        : text.vert
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat3 ndc;

void main() {
    vec3 ndc_position = ndc * vec3(aPos, 1.0);
    gl_Position = vec4(ndc_position, 1.0);
    TexCoord = aTexCoord;
}