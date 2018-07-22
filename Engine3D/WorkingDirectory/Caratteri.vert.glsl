/*
Vertex shader to render characters
*/

#version 330 core

// --- Inputs made from arrays ---
layout(location = 0) in vec2 vertex; // Position of the summit
layout(location = 1) in vec2 coordUV; // UV position

out vec2 UV;

uniform mat4 MVP;


void main()
{
	// Output position of the vertex, in clip space: MVP * position
	gl_Position = MVP * vec4(vertex, 0.0f, 1.0f);

	// UV of the vertex. No special space for this one.
	UV = coordUV;
}