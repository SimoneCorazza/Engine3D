#version 330 core

/*
Vertex shader to render a skybox
*/

layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 MVP;


void main()
{
    gl_Position = MVP * vec4(position, 1);
	// As the coordinate of the skybox directly step the coordinate of the summit (even if not normalized it does not matter, it will be normalized by the system)
    TexCoords = position;
}  