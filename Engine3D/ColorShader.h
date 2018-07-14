#pragma once
/*

#include "ModelShader.h"

// Shades for mono colored vertices
class ColorShader : public ModelShader
{
	GLuint idMatrix; // ID of the uniform variable of the array
	GLuint idColor; // ID of the uniform color variable to use

	public:
		ColorShader();
		~ColorShader();

	// METHODS:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		// DRAWING:

		void RenderTriangles(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix, GLsizei numVerteces);
		void RenderLines(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix, GLsizei numVerteces);

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;


	private:

		// Render with the indicated primitive
		void RenderPrimitives(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix, GLsizei numVerteces, GLenum Primitive) const;
};

*/