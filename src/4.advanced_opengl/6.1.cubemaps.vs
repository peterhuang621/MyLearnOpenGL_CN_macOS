#version 330 core
layout(location = 0) in vec3 aPos;
// layout(location = 1) in vec2 aTexCoords;
// out vec2 TexCoords;

// environment-mapping
layout(location = 1) in vec3 aNormal;
out vec3 Normal, Position;

uniform mat4 projection,view,model;

void main(){
    // TexCoords=aTexCoords;
    // gl_Position=projection*view*model*vec4(aPos,1.0);
    
    // environment-mapping
    Normal=mat3(transpose(inverse(model)))*aNormal;
    Position=vec3(model*vec4(aPos,1.0));
    gl_Position=projection*view*model*vec4(aPos,1.0);
}