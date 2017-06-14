#include "SkyboxShader.h"

#include "Skybox.h"
#include "TextureCube.h"
#include "Mesh.h"


SkyboxShader::SkyboxShader()
{
}


SkyboxShader::~SkyboxShader()
{
}

void SkyboxShader::RenderSkybox(const Skybox * S, const glm::mat4 & CameraMatrix, const glm::vec3& CameraPos)
{
	glm::mat4 mvp = CameraMatrix * S->getMatrix(CameraPos);
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &mvp[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(idCubeSampler, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, S->getTextureCube()->getTextureID());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, S->getMesh()->getIDBuffVerteces());
	glVertexAttribPointer(
		0,								// ID attribute
		3,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		0,								// stride
		(void*)0						// array buffer offset
		);

	glDrawArrays(GL_TRIANGLES, 0, S->getMesh()->getVertecesDraw());
	glDisableVertexAttribArray(0);

	//Setto nessuna texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SkyboxShader::LoadIDVar()
{
	idMatrix = GetVarID("MVP");
	idCubeSampler = GetVarID("skybox");
}
