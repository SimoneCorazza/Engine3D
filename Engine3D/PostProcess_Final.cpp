#include "PostProcess_Final.h"



PostProcess_Final::PostProcess_Final()
{
}


PostProcess_Final::~PostProcess_Final()
{
}




void PostProcess_Final::DrawFrame(GLuint UnitBuffVertex, GLuint TexID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexID);
	// Set our "renderedTexture" sampler to user Texture Unit 0
	glUniform1i(idTextureSampler, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, UnitBuffVertex);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
}

void PostProcess_Final::LoadIDVar()
{
	idTextureSampler = GetVarID("myTextureSampler");
}
