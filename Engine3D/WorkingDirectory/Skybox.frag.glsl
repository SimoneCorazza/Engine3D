#version 330 core

/*
Fragment shader to render the skybox
*/

in vec3 TexCoords; // Texture coordinate (can be the same vertex of the mesh)
uniform samplerCube skybox; // Sampler fo the textured cube of the skybox

out vec4 colorOut;

void main()
{
	// NOTE: before the X was inverted [TexCoords.x * (-1)] we do not know why (problem solved?)
	// Invert the Y as the texture loading does not reverse the rows
    colorOut = texture(skybox, vec3(TexCoords.x, TexCoords.y * (-1), TexCoords.z));
}