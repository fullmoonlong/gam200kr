#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat3 ndc;
uniform int frameX;
uniform int frameY;
uniform int frameIndex;
uniform float correction;

void main()
{
    float unitWidth = 1.0 / frameX;
    float unitHeight = 1.0 / frameY;

    vec3 ndc_position = ndc * vec3(aPos, 1.0);
    gl_Position = vec4(ndc_position.xy, 0.0, 1.0);

    TexCoord.x = (aTexCoord.x * unitWidth + unitWidth * (frameIndex % frameX));
    //TexCoord.y = (aTexCoord.y * unitHeight + unitHeight * (2 - frameIndex / frameX));
    TexCoord.y = aTexCoord.y;
}