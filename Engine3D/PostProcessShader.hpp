#pragma once

#include <GL\glew.h>

#include "Shader.hpp"

class PostProcessShaderParams;

// Abstract class representing a shader dedicated to the modification of a rendered image
class PostProcessShader : public Shader
{
	GLuint idRenderedTexture; // ID of the texture containing the rendered frame
	GLuint idDepthTexture; // ID of the texture containing the depth in the frame

	public:
		PostProcessShader();
		~PostProcessShader();


	public:

		// Apply the shader
		// @param [in] IdBufferUnitQuad - Id of the buffer containing a square of side 2 with the center in the origin
		// and consists of two triangles (6 vertices in the buffer)
		// @param [in] RenderedTextureID - Texture ID according to OpenGL of the rendered frame
		// @param [in] DepthTextureID - Texture ID according to OpenGL of the depth buffer of the rendered scene
		// @param [in] Params - Parameters for the shader
		void ApplayShader(GLuint IdBufferUnitQuad, GLuint RenderedTextureID, GLuint DepthTextureID, const PostProcessShaderParams* Params) const;

	protected:

		// Method to derive that allows you to set the parameters
		// @param [in] Params - Parameters for the shader
		virtual void SetShaderParams(const PostProcessShaderParams* Params) const abstract;

		void LoadIDVar() override;
};

