/**************************************************************************************
 *	File Name        : shape.vert
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#version 330
layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;

out vec4 outColor;

uniform mat3 ndc;

void main()
{
    vec3 ndc_position = ndc * vec3(position, 1.0);
    gl_Position = vec4(ndc_position.xy, 0.0, 1.0);
    outColor = color;
}