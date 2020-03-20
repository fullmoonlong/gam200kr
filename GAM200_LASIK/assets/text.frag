/**************************************************************************************
 *	File Name        : text.frag
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D outTexture;
uniform vec4 uniformColor;

void main() {
    vec4 color = texture(outTexture, TexCoord);
    if (color.a == 0.0)
        discard;
    FragColor = color * uniformColor;
}