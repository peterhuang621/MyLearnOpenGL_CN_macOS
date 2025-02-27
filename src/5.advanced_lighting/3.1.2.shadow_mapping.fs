#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture,shadowMap;

uniform vec3 lightPos,viewPos;

vec3 lightDir,normal;

float ShadowCalculation(vec4 fragPosLightSpace){
    vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
    projCoords=projCoords*0.5+0.5;
    float closetDepth=texture(shadowMap,projCoords.xy).r;
    float currentDepth=projCoords.z;
    float bias=max(0.05*(1.0-dot(lightDir,normal)),0.005);
    // float shadow=currentDepth-bias>closetDepth?1.0:0.0;

    // PCF
    float shadow=0.0;
    vec2 texelSize=1.0/textureSize(shadowMap,0);
    for(int x=-1;x<=1;x++){
        for(int y=-1;y<=1;y++){
            float pcfDepth=texture(shadowMap,projCoords.xy+texelSize*vec2(x,y)).r;
            shadow+=currentDepth-bias>pcfDepth?1.0:0.0;
        }
    }

    if(projCoords.z>1.0)shadow=0.0;

    return shadow/9.0;
}

void main()
{           
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);

    vec3 ambient = 0.3 * lightColor;

    lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}
