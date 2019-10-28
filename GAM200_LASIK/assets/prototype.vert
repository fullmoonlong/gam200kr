#version 330
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;

out vec4 outColor;

uniform mat3 ndc;

void main()
{
    vec3 p  = ndc * vec3(aPos, 1.0);
    gl_Position = vec4(p.xy, 0.0, 1.0);
    outColor = aColor;
}