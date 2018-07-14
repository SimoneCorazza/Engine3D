#pragma once

#include "Shader.h"

// Shader used to render the final camera frame
// on the screen
class PostProcess_Final : public Shader
{
	GLuint idTextureSampler;

	public:
		PostProcess_Final();
		~PostProcess_Final();

	public:

		// Screen the final camera frame
		// @param [in] UnitBuffVertex - Buffer of the 6 vertices of the screen (two triangles)
		// NOTE: as no height and length operations are carried out on the vertices
		// of the screen will always be 1
		// @param [in] TexID - Texture representing the camera frame
		void DrawFrame(GLuint UnitBuffVertex, GLuint TexID);

	protected:

		void LoadIDVar() override;
};

