#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};

struct DirLight {
    vec3 direction;
	vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLight;

uniform sampler2D texture_diffuse0;
uniform bool hasDiffuseTexture;
uniform sampler2D depthMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir);
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);


void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result =  CalcDirLight(dirLight, norm, viewDir);
  
    FragColor = vec4(result, material.alpha);
}



float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
   
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(depthMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    
    float shadow = 0.0;
    shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    
    // //阴影锯齿消除
    // vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    // //均值滤波
    // for(int x = -1; x <= 1; ++x)
    // {
    //     for(int y = -1; y <= 1; ++y)
    //     {
    //         float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
    //         shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
    //     }    
    // }
    // shadow /= 9.0;
    if(projCoords.z > 1.0)
        shadow = 0.0;
    

    return shadow;
}



vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{

    vec3 lightDir = normalize(-light.direction);
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

    float shadow = ShadowCalculation(FragPosLightSpace, normal, lightDir);                      
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) ;    
    return result;

}