/*
Vertex shader that moves the vertexes outward
As a fragment shader anything standard works, for example Texture.frag.glsl
*/

#version 330 core

// Input from the buffers associated with the current vertex
layout(location = 0) in vec3 vertexPos; // Position in the game world
layout(location = 1) in vec2 vertexUV; // UV coordinates of the vertex
layout(location = 2) in vec3 vertexNorm; // Summit normals

out vec2 UV; // Interpolated UV coordinates for the fragment shader

uniform mat4 MVP; // MVP matrix
uniform float delta; // Moving the polygons

void main()
{
	vec3 d = vertexNorm * delta;
	gl_Position = MVP * vec4(vertexPos + d, 1);
	UV = vertexUV;
}