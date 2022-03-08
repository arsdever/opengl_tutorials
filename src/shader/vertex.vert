#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv_coords;
layout (location = 3) in vec3 normalVector;

out vec4 outColor;
out vec2 uvCoords;
out vec3 Normal;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 camera;

void main()
{
    gl_Position = camera * transform * vec4(pos, 1.0);
    outColor = color;
    uvCoords = uv_coords;
    Normal = normalVector;
    fragPos = vec3(transform * vec4(pos, 1.0));
}