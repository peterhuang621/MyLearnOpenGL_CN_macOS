#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseMap,normalMap,depthMap;

uniform vec3 lightPos,viewPos;
uniform float heightScale;

vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir){
    const float minLayers=8, maxLayers=32;
    float numLayers=mix(maxLayers,minLayers,abs(dot(vec3(0.0,0.0,1.0),viewDir)));
    float layerDepth=1.0/numLayers;
    float currentLayerDepth=0.0;
    vec2 P=viewDir.xy/viewDir.z*heightScale;
    vec2 deltaTexCoords=P/numLayers;

    vec2 currentTexCoords=texCoords;
    float currentDepthMapValue=texture(depthMap,currentTexCoords).r;

    while(currentLayerDepth<currentDepthMapValue){
        currentTexCoords-=deltaTexCoords;
        currentDepthMapValue=texture(depthMap,currentTexCoords).r;
        currentLayerDepth+=layerDepth;
    }

    // Parallex Occlusion Mapping
    vec2 prevTexCoords=currentTexCoords+deltaTexCoords;
    float afterDepth=currentDepthMapValue-currentLayerDepth;
    float beforeDepth=texture(depthMap,prevTexCoords).r-currentLayerDepth+layerDepth;

    float weight=afterDepth/(afterDepth-beforeDepth);
    vec2 finalTexCoords=prevTexCoords*weight+currentTexCoords*(1.0-weight);

    // float height=texture(depthMap,texCoords).r;
    // return texCoords-viewDir.xy*(height*heightScale);
    return finalTexCoords;
}

void main(){
    vec3 viewDir=normalize(fs_in.TangentViewPos-fs_in.TangentFragPos);
    vec2 texCoords=ParallaxMapping(fs_in.TexCoords,viewDir);
    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)discard;

    vec3 normal=texture(normalMap,texCoords).rgb;
    normal=normalize(normal*2.0-1.0);

    vec3 color=texture(diffuseMap,texCoords).rgb;
    vec3 ambient=0.1*color;

    vec3 lightDir=normalize(fs_in.TangentLightPos-fs_in.TangentFragPos);
    float diff=max(dot(lightDir,normal),0.0);
    vec3 diffuse=diff*color;

    vec3 halfwayDir=normalize(lightDir+viewDir);
    float spec=pow(max(dot(normal,halfwayDir),0.0),32.0);

    vec3 specular=vec3(0.2)*spec;
    FragColor=vec4(ambient+diffuse+specular,1.0);
}