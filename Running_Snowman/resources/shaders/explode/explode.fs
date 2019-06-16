#version 330 core
out vec4 FragColor;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};

in vec2 TexCoords;
uniform Material material;


void main()
{    
   
    vec3 result =  material.diffuse;

    FragColor = vec4(result, 1.0);
}


