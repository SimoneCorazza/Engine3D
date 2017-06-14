#version 330 core

/*
Fragment shader per lo skybox
*/

in vec3 TexCoords; //Coordinata della texture (può essere lo stesso vertice della mesh)
uniform samplerCube skybox; //Sampler delal textured cube dello skybox

out vec4 colorOut;

void main()
{
	//NOTA: prima la X si invertiva [TexCoords.x * (-1)] non si sa il perchè (problema risolto?)
	//Inverto la Y siccome il caricamento della texture non inverte le righe
    colorOut = texture(skybox, vec3(TexCoords.x, TexCoords.y * (-1), TexCoords.z));
}