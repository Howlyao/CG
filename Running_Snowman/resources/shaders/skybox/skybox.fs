#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox1;
uniform samplerCube skybox2;
uniform float rate;

void main()
{    
    FragColor = mix(texture(skybox1, TexCoords), texture(skybox2, TexCoords), rate);
}