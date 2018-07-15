#include "ColorShader.h"
/*
#include "DEBUG.h"

ColorShader::ColorShader()
{
	idMatrix = 0;
	idColor = 0;
}

ColorShader::~ColorShader()
{
}

void ColorShader::LoadIDVar()
{
	idMatrix = GetVarID("MVP");
	idColor = GetVarID("color");
}

void ColorShader::SetAmbientLight(const glm::vec3 & L)
{
	// I do not consider the lights in this shader
}

void ColorShader::SetSceneLights(const std::vector<Light*>& Lights)
{
	// I do not consider the lights in this shader
}

void ColorShader::SetMaterial(const Material * M)
{
	// I do not consider the material in this shader
}

void ColorShader::SetCameraParameters(const glm::mat4 & ViewMatix, const glm::mat4 & ProjectionMatrix)
{
	// I do not use this method
}

void ColorShader::RenderTriangles(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4 & modelMatrix, const glm::mat4 & cameraMatrix, GLsizei numVerteces)
{
	RenderPrimitives(vertexBufer, Color, modelMatrix, cameraMatrix, numVerteces, GL_TRIANGLES);
}

void ColorShader::RenderLines(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4 & modelMatrix, const glm::mat4 & cameraMatrix, GLsizei numVerteces)
{
	RenderPrimitives(vertexBufer, Color, modelMatrix, cameraMatrix, numVerteces, GL_LINES);
}

void ColorShader::SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix)
{
	ASSERT(false, "Not implemented: ColorShader::RenderModel()");
}

void ColorShader::RenderPrimitives(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4 & modelMatrix, const glm::mat4 & cameraMatrix, GLsizei numVerteces, GLenum Primitive) const
{
	glm::mat4 mvp = cameraMatrix * modelMatrix;
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &mvp[0][0]);

	glUniform4f(idColor, Color.r, Color.g, Color.b, Color.a);

	// Attribute buffer: vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufer);
	glVertexAttribPointer(
		0,								// attribute. No particular reason for 0, but must match the layout in the shader.
		3,								// size
		GL_FLOAT,						// type
		GL_FALSE,						// normalized?
		0,								// stride
		(void*)0						// offset buffer array
		);


	glDrawArrays(Primitive, 0, numVerteces);

	glDisableVertexAttribArray(0);

	// I leave no texture
	glBindTexture(Primitive, 0);
}

*/