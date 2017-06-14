/*
Vertex shader per spostare 
Come fragment shader basta reciclarne uno standard che mostra la texture e basta (Texture.frag.glsl)
*/

#version 330 core

//Input provenienta dai buffer associati al vertice attuale
layout(location = 0) in vec3 vertexPos; //Posizione nel mondo di gioco
layout(location = 1) in vec2 vertexUV; //Coordinate UV del vertice
layout(location = 2) in vec3 vertexNorm; //Normali del vertice

out vec2 UV; //Coordinate UV interpolate per il fragment shader

uniform mat4 MVP; //Matrice MVP
uniform float delta; //Spostamento dei poligoni

void main()
{
	vec3 d = vertexNorm * delta;
	gl_Position = MVP * vec4(vertexPos + d, 1);
	UV = vertexUV;
}