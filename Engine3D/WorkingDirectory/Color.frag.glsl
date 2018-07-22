#version 330 core

// Output data
out vec4 colorOut;

// Values ​​that stay constant for the whole mesh.
uniform vec4 color;

void main()
{
	colorOut = color;
}