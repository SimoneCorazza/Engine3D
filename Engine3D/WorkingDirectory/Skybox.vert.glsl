#version 330 core

/*
Vertex shader per lo skybox
*/

layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform mat4 MVP;


void main()
{
    gl_Position = MVP * vec4(position, 1);
	//Come coordinata dello skybox passo direttamente la coordinata del vertice (anche se non normalizzata non importa, verrà normalizzata dal sistema)
    TexCoords = position;
}  