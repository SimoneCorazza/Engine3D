#include "ModelShader.h"

#include "CommonConstants.h"

ModelShader::ModelShader()
{
	idVertecesCoords = INVALID_BUFFER_ID;
	idVertecesUVs = INVALID_BUFFER_ID;
	idVertecesNormals = INVALID_BUFFER_ID;
}


ModelShader::~ModelShader()
{
}

GLuint ModelShader::getIDVertecesCoords() const
{
	return idVertecesCoords;
}

GLuint ModelShader::getIDVertecesUVs() const
{
	return idVertecesUVs;
}

GLuint ModelShader::getIDVertecesNormals() const
{
	return idVertecesNormals;
}

bool ModelShader::getBothSide() const
{
	return bothSide;
}
