#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform bool hdr;
uniform float exposure;

void main(){
    const float gamma=2.2;
    vec3 hdrColor=texture(hdrBuffer,TexCoords).rgb;
    vec3 result;
    if(hdr){
        result=vec3(1.0f)-exp(-hdrColor*exposure);
        result=pow(result,vec3(1.0/gamma));
    }else{
        result=pow(hdrColor,vec3(1.0/gamma));
    }
    FragColor=vec4(result,1.0f);
}