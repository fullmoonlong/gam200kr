/**************************************************************************************
 *	File Name        : animation.frag
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 color = texture(ourTexture, TexCoord);

    if (color.a == 0.0)
        discard;
    FragColor = color;
}