#version 330 core
layout (location = 0) in vec2 vertex; 
layout (location = 1) in vec2 aTexCoords;

out vec4 ParticleColor;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float scale;
uniform vec4 color;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4((vertex.xy * scale), 0.0, 1.0);
}