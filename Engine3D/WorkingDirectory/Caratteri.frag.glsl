/*
Fragment shader creato per disegnare dei caratteri
*/

#version 330 core

in vec2 UV;

out vec4 fragOut;

uniform sampler2D texChar; //Texture contenente il carattere da renderizzare
uniform vec4 color; //Colore del carattere

void main()
{
	fragOut = color * texture2D(texChar, UV).r; //Calcolo il colore risultante
}