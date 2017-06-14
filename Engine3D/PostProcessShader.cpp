#include "PostProcessShader.h"

#include "ShaderLoader.h"
#include "DEBUG.h"

#define NAME_TEXTURE_RENDERED "renderedTex"
#define NAME_TEXTURE_DEPTH "depthTex"

PostProcessShader::PostProcessShader()
{
	idRenderedTexture = UINT_MAX;
	idDepthTexture = UINT_MAX;
}


PostProcessShader::~PostProcessShader()
{
}



void PostProcessShader::ApplayShader(GLuint IdBufferUnitQuad, GLuint RenderedTextureID, GLuint DepthTextureID, const PostProcessShaderParams* Params) const
{
	ASSERT(idRenderedTexture != UINT_MAX || idDepthTexture != UINT_MAX, 
		"the derived class of PostProcessSHader if overrides the method CaricaIDVariabili must call the base method with PostProcessShader::CaricaIDVariabili();");

	SetShaderParams(Params); //Setta i parametri dello shader

	if (idRenderedTexture != UINT_MAX) //Controllo se il post process derivato utilizza la texture renderizzata
	{
		//Imposto la texture renderizzata nello shader
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, RenderedTextureID);
		glUniform1i(idRenderedTexture, 0);
	}

	if (idDepthTexture != UINT_MAX) //Controllo se il post process derivato utilizza la depth texture
	{
		//Imposto la texture della profonditÓ nello shader
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, DepthTextureID);
		glUniform1i(idDepthTexture, 1);
	}


	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, IdBufferUnitQuad);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, 6); //Disegno il quadrato

	glDisableVertexAttribArray(0);
}

void PostProcessShader::LoadIDVar()
{
	idRenderedTexture = GetVarID(NAME_TEXTURE_RENDERED);
	idDepthTexture = GetVarID(NAME_TEXTURE_DEPTH);

	ASSERT(idRenderedTexture != UINT_MAX || idDepthTexture != UINT_MAX,
		"the created shader must have two texture sampler named with the value of the macro: NAME_TEXTURE_RENDERED  (for the rendered texture) and  NAME_TEXTURE_DEPTH (for the depth texture)");
}


