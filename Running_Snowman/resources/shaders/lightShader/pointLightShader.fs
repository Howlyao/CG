#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};

struct PointLight {
    vec3 pos;
	vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform sampler2D texture_diffuse0;
uniform bool hasDiffuseTexture;
uniform samplerCube depthMap;

uniform PointLight pointLight;
uniform Material material;
uniform vec3 viewPos;

uniform float far_plane;



float ShadowCalculation(vec3 fragPos, vec3 lightPos);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);


void main()
{           

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result =  CalcPointLight(pointLight, norm, viewDir);
    FragColor = vec4(result, material.alpha);
    
}

float ShadowCalculation(vec3 fragPos, vec3 lightPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // ise the fragment to light vector to sample from the depth map    
    float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.80; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
      
    return shadow;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{

    vec3 lightDir = normalize(light.pos - FragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient, diffuse, specular;
    if (!hasDiffuseTexture) {
        ambient = light.ambient * material.ambient * light.color;
        diffuse = light.diffuse * diff * material.diffuse * light.color;
        specular = light.specular * spec * material.specular * light.color;
        
    } else {
        ambient = light.ambient * texture(texture_diffuse0, TexCoords).rgb * light.color;
        diffuse = light.diffuse * diff * texture(texture_diffuse0, TexCoords).rgb * light.color;
        specular = light.specular * spec * material.specular * light.color;
    
    }

    float shadow = ShadowCalculation(FragPos, light.pos);                      
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)); 
    // vec3 result = (ambient + (1.0) * (diffuse + specular)); 
    
    return result;

}