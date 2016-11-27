#version 120
varying vec3 TexCoords;
vec4 color;

uniform samplerCube skybox;

void main()
{    
    gl_FragColor.rgb = textureCube(skybox, TexCoords).rgb;
}