/*
Vertex shader shared between all post process effects
*/

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

out vec2 UV; // UV to pass to the fragment shader

void main()
{
	// Output position of the vertex, in clip space: MVP * position
	gl_Position =  vec4(vertexPosition_modelspace, 1);
	
	UV = (vertexPosition_modelspace.xy + vec2(1,1)) / 2.0;
}