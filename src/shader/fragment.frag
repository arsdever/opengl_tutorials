#version 330 core

out vec4 FragColor;

in vec4 outColor;
in vec2 uvCoords;

uniform sampler2D mainTexture;

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    FragColor = texture(mainTexture, uvCoords);
}