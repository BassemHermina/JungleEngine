#version 120
attribute vec3 position;
varying vec3 TexCoords;

uniform mat4 projection;
uniform mat4 VM;


void main()
{
    vec4 pos = projection * VM * vec4(position, 1.0);
    gl_Position = pos.xyzw;
    TexCoords = -position; // el minus di mn 3ndi 3ashan t3dl l 7agat el m2loba bas
    // da le3b fi orinetation l sewar 
}  