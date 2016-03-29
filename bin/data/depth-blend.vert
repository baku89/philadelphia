#version 120
#define GLSLIFY 1

uniform vec2 resolution;

varying vec2 uv;


void main(){
	
	uv = gl_Vertex.xy;

	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}