#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat3 ndc;
uniform int frameX;
uniform int frameIndex;
uniform float correction;

void main()
{
    float unitWidth = 1.0 / frameX;

    vec3 ndc_position = ndc * vec3(aPos, 1.0);
    gl_Position = vec4(ndc_position, 1.0);

    TexCoord.x = (aTexCoord.x * unitWidth + unitWidth * frameIndex) - correction;
    TexCoord.y = aTexCoord.y;
}