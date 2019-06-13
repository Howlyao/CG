#version 330 core

out vec4 FragColor;
in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};


uniform float snowmanHeight;
uniform Material material;

void main()
{    
    
    if (FragPos.y > snowmanHeight) {
        discard;
    }
    FragColor = vec4(material.diffuse, material.alpha);
}


