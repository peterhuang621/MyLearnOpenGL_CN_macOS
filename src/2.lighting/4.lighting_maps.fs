#version 330 core
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    // exercise 4
    sampler2D emission;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
// exercise 4    
// uniform vec3 matrixlight;
// uniform float matrixmove;

void main(){
    vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoords));
    
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(norm,lightDir),0.0);
    vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCoords).rgb;

    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    // vec3 specular=light.specular*(spec*material.specular);
    // exercise 2
    // vec3 specular=light.specular*(spec*(vec3(1.0f)-texture(material.specular,TexCoords).rgb));
    vec3 specular=light.specular*(spec*texture(material.specular,TexCoords).rgb);

    // exercise 4    
    // vec3 emission=matrixlight*texture(material.emission, vec2(TexCoords.x,TexCoords.y+matrixmove)).rgb;
    // vec3 result=ambient+diffuse+specular+emission;
    
    vec3 result=ambient+diffuse+specular;
    FragColor=vec4(result,1.0);
}