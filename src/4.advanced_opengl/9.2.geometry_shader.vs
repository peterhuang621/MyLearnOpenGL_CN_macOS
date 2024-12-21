#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT{
    vec2 texCoords;
}vs_out;

uniform mat4 model,view,projection;

void main(){
    vs_out.texCoords=aTexCoords;
    gl_Position = projection * view * model * vec4(aPos*0.1, 1.0); 
}