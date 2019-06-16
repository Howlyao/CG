// #version 330 core
// out vec4 FragColor;

// in vec2 TexCoords;
// in vec3 Normal;
// in vec3 FragPos;
// in vec4 FragPosLightSpace;

// struct Material {
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
//     float shininess;
//     float alpha;
// };

// struct DirLight {
//     vec3 direction;
// 	vec3 color;
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
// };

// uniform float snowmanHeight;
// uniform Material material;
// uniform vec3 viewPos;
// uniform DirLight dirLight;

// uniform sampler2D texture_diffuse0;
// uniform bool hasDiffuseTexture;
// uniform sampler2D depthMap;

// float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir);
// vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);


// void main()
// {    
    
//     vec3 norm = normalize(Normal);
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 result =  CalcDirLight(dirLight, norm, viewDir);
    
   
//     // if (FragPos.y <= snowmanHeight) {
//     //     FragColor = vec4(result, material.alpha);
//     // } else {
//     //     FragColor = vec4(result, 1.0f);
//     // }
//     FragColor = vec4(result, material.alpha);
// }



// float ShadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
// {
   
//     // perform perspective divide
//     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//     // transform to [0,1] range
//     projCoords = projCoords * 0.5 + 0.5;
//     // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
//     float closestDepth = texture(depthMap, projCoords.xy).r; 
//     // get depth of current fragment from light's perspective
//     float currentDepth = projCoords.z;
//     // check whether current frag pos is in shadow
//     float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    
//     float shadow = 0.0;
//     shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    
//     // //阴影锯齿消除
//     // vec2 texelSize = 1.0 / textureSize(depthMap, 0);
//     // //均值滤波
//     // for(int x = -1; x <= 1; ++x)
//     // {
//     //     for(int y = -1; y <= 1; ++y)
//     //     {
//     //         float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
//     //         shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
//     //     }    
//     // }
//     // shadow /= 9.0;
//     if(projCoords.z > 1.0)
//         shadow = 0.0;
    

//     return shadow;
// }



// vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
// {

//     vec3 lightDir = normalize(-light.direction);
//     // diffuse shading
//     float diff = max(dot(normal, lightDir), 0.0);
//     // specular shading
//     vec3 reflectDir = reflect(-lightDir, normal);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//     // combine results
//     vec3 ambient, diffuse, specular;
//     if (!hasDiffuseTexture) {
//         ambient = light.ambient * material.ambient * light.color;
//         diffuse = light.diffuse * diff * material.diffuse * light.color;
//         specular = light.specular * spec * material.specular * light.color;
        
//     } else {
//         ambient = light.ambient * texture(texture_diffuse0, TexCoords).rgb * light.color;
//         diffuse = light.diffuse * diff * texture(texture_diffuse0, TexCoords).rgb * light.color;
//         specular = light.specular * spec * material.specular * light.color;
    
//     }

//     float shadow = ShadowCalculation(FragPosLightSpace, normal, lightDir);                      
//     vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) ;    
//     return result;

// }

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
    // float bias = 0.05; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    // float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        
    // display closestDepth as debug (to visualize depth cubemap)
    // FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    

    float shadow = 0.0;
    float bias = 0.05; 
    float samples = 4.0;
    float offset = 0.1;
    
    for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    {
        for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        {
            for(float z = -offset; z < offset; z += offset / (samples * 0.5))
            {
                float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r; 
                closestDepth *= far_plane;   // Undo mapping [0;1]
                if(currentDepth - bias > closestDepth)
                    shadow += 1.0;
            }
        }
    }
    
    shadow /= (samples * samples * samples);


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
    //  vec3 result = (ambient + (1.0) * (diffuse + specular)); 
    return result;

}