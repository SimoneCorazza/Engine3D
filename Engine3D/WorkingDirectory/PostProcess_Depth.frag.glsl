#version 330 core

uniform sampler2D renderedTex;
uniform sampler2D depthTex;

in vec2 UV;
out vec4 color;

void main()
{
	color = texture2D(depthTex, UV);
}