#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
out vec4 outColor;

uniform mat4 transform;
uniform mat4 camera;

void main()
{
    gl_Position = camera * transform * vec4(pos.x, pos.y, pos.z, 1.0);
    outColor = color;
}