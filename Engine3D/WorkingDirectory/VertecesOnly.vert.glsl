/*
Vertex shader con un array per i vertici
*/

#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace; //Array dei vertici

uniform mat4 MVP; //Matrice per lo shader


void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace, 1);
}