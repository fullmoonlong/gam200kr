/**************************************************************************************
 *	File Name        : particle.vert
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#version 330
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec4 outColor;
out vec2 outTexCoords;

uniform mat3 ndc;
uniform vec2 offset;
uniform vec4 color;

void main() {
    float scale = 10.0;
    vec3 ndc_position = ndc * vec3(position, 1.0);
    gl_Position = vec4((ndc_position.xy * scale) + offset, 0.0, 1.0);
    outColor = color;
    outTexCoords = texCoords;
}