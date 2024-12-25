#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;
layout (location = 3) in vec2 aOffset2;

out vec3 fColor;

void main()
{
    fColor = aColor;
    // Make it fun!
    // vec2 pos = aPos * (gl_InstanceID / 100.0);
    if(gl_InstanceID<30){
        gl_Position = vec4(aPos + aOffset, 0.0, 1.0);
    }else{
        gl_Position = vec4(aPos + aOffset2, 0.0, 1.0);
    }
}
