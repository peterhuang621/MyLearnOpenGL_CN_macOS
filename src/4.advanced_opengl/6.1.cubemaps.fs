#version 330 core
out vec4 FragColor;

// in vec2 TexCoords;

// uniform sampler2D texture1;

// environment-mapping
in vec3 Normal, Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main(){
    // FragColor=texture(texture1,TexCoords);
    
    // environment-mapping
    // vec3 I = normalize(Position - cameraPos);
    // vec3 R = reflect(I, normalize(Normal));
    // FragColor = vec4(texture(skybox, R).rgb*0.5, 1.0);


    // Refraction
    float ratio=1.00/1.52;
    vec3 I=normalize(Position-cameraPos);
    vec3 R=refract(I,normalize(Normal),ratio);
    FragColor=vec4(texture(skybox,R).rgb,1.0);
}