/*
Simplest vertex shader
*/

#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace; // Array of the vertices

uniform mat4 MVP; // Matrix for the shader


void main()
{
	// Output position of the vertex, in clip space: MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
}