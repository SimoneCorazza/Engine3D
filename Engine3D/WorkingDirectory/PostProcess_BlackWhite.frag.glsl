/*
Fragment shader that take in a texture and output a black and white texture 
*/


#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D renderedTex;

void main()
{
	vec4 texColor = texture2D(renderedTex, UV);
	float gray = 0.299 * texColor.r + 0.587 * texColor.g + 0.114 * texColor.b;
    color = vec4(gray, gray, gray, texColor.a);
}