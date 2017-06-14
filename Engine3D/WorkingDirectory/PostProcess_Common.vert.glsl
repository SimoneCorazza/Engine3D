/*
Vertex shader utilizzato come shader comune per i vertici del post procesing effecs
*/

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

out vec2 UV; //UV da passare al fragment shader

void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  vec4(vertexPosition_modelspace, 1);
	
	UV = (vertexPosition_modelspace.xy + vec2(1,1)) / 2.0;
}