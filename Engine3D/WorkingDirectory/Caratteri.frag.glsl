/*
Fragment to render characters
*/

#version 330 core

in vec2 UV;

out vec4 fragOut;

uniform sampler2D texChar; // Texture containing the character to render
uniform vec4 color; // Font color

void main()
{
	fragOut = color * texture2D(texChar, UV).r; // Calculate the resulting color
}