#version 120


attribute vec3 vertex_screenspace; //in
attribute vec2 vertexUV; //in
varying vec2 var_vertexUV; //out to fragment shader

void main(){

    gl_Position = vec4(vertex_screenspace, 1); //out to screen
	var_vertexUV = vertexUV; //out to fragment shader
}