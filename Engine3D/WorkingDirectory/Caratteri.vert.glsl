/*
Vertex shader creato per disegnare dei caratteri
*/

#version 330 core

// --- Input effettuati dagli array ---
layout(location = 0) in vec2 vertex; //Posizione del vertice
layout(location = 1) in vec2 coordUV; //Posizione delle UV

out vec2 UV;

uniform mat4 MVP;


void main()
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertex, 0.0f, 1.0f);

	// UV of the vertex. No special space for this one.
	UV = coordUV;
}