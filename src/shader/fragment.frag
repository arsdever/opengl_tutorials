#version 330 core

out vec4 FragColor;

struct light
{
    vec3 position;
    vec4 color;
    float intencity;
};

in vec4 outColor;
in vec2 uvCoords;
in vec3 Normal;
in vec3 fragPos;

uniform sampler2D mainTexture;
uniform light _light[4];

void main()
{
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(_light[0].position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    FragColor = texture(mainTexture, uvCoords) * (diff + .1f);
    //FragColor = vec4(_light[0].position, 1);
    //FragColor = vec4(1);
}