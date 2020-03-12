/**************************************************************************************
 *	File Name        : particle.frag
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#version 330
in vec4 outColor;
in vec2 outTexCoords;

out vec4 color;

uniform sampler2D sprite;

void main() {
    vec4 calculatedColor = texture(sprite, outTexCoords) * outColor;
    if (calculatedColor.a == 0.0)
        discard;
    color = calculatedColor;
}