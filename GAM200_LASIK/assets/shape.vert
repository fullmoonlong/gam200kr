#version 330
layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;
in vec2 aTexCoord;

out vec4 outColor;
out vec2 TexCoord;
uniform mat3 NDC;

void main()
{
    vec3 p = vec3(position, 1.0);
    vec3 ndc_version = NDC * p;
    gl_Position = vec4(ndc_version.xy, 0.0, 1.0);
    outColor = color;
    TexCoord = aTexCoord;
}