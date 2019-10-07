#version 330
in vec2 position;
in vec4 color;
out vec4 outColor;
uniform mat3 NDC;

void main()
{
    vec3 p = vec3(position, 1.0);
    vec3 ndc_version = NDC * p;
    gl_Position = vec4(ndc_version.xy, 0.0, 1.0);
    outColor = color;
}