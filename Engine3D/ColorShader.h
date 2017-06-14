#pragma once
/*

#include "ModelShader.h"

//Shader per vertici mono colorati
class ColorShader : public ModelShader
{
	GLuint idMatrix; //ID della variabile uniforme della matrice
	GLuint idColor; //ID della variabile uniforme del colore da usare

	public:
		ColorShader();
		~ColorShader();

	//METODI:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		//DISEGNO:

		void RenderTriangles(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix, GLsizei numVerteces);
		void RenderLines(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix, GLsizei numVerteces);

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;


	private:

		//Renderizza con la primitiva indicata
		void RenderPrimitives(GLuint vertexBufer, const glm::vec4 Color, const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix, GLsizei numVerteces, GLenum Primitive) const;
};

*/