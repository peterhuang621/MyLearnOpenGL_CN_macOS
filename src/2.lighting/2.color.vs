#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// exercise 2
// uniform vec3 lightPos;
// out vec3 LightPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos=vec3(model*vec4(aPos,1.0));
    Normal=aNormal;
    // exercise 2
    // FragPos=vec3(view*model*vec4(aPos,1.0));
    // Normal=mat3(transpose(inverse(view*model)))*aNormal;
    // LightPos=vec3(view*vec4(lightPos,1.0));
}

// exercise 3
// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;

// out vec3 result;

// uniform vec3 lightColor;
// uniform vec3 viewPos;
// uniform vec3 lightPos;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

// void main(){
//     gl_Position = projection * view * model * vec4(aPos, 1.0);
//     vec3 Position=vec3(model*vec4(aPos,1.0));
//     vec3 Normal=mat3(transpose(inverse(model)))*aNormal;

//     float ambientStrength=0.1;
//     vec3 ambient=ambientStrength*lightColor;
    
//     vec3 norm=normalize(Normal);
//     vec3 lightDir=normalize(lightPos-Position);
//     float diff=max(dot(norm,lightDir),0.0);
//     vec3 diffuse=diff*lightColor;

//     float specularStrength = 0.5;
//     vec3 viewDir=normalize(viewPos-Position);
//     vec3 reflectDir=reflect(-lightDir,norm);
//     float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
//     vec3 specular=specularStrength*spec*lightColor;
//     result=ambient+diffuse+specular;
// }