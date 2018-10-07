#pragma once

#include "Shader.hpp"
#include "Light.hpp"
#include <vector>

class Model;
class Mesh;
class Material;
class Actor;
class ActorParameters;

// Abstract class representing a generic shader for rendering a model
class ModelShader : public Shader
{
	protected:
		GLuint idVertecesCoords; // ID of the array of the coordinates of the vertices (must be present)
		GLuint idVertecesUVs; // ID of the array with the uv of the vertices (if not present, do not set it or set it to INVALID_BUFFER_ID)
		GLuint idVertecesNormals; // ID of the array the normals of the vertices (if not present, do not set it or set it to INVALID_BUFFER_ID)

		bool bothSide = false; // Flag indicating whether the shader requires both sides of the polygons to be rendered

	public:
		ModelShader();
		~ModelShader();


	public:

		// Gets the ID of the shader variable that contains the coodinate buffer array (x, y, z)
		GLuint getIDVertecesCoords() const; // ADD THE VARIOUS IDENTURES OF THE ATTRIBUTES OF THE TOPS
		// Gets the ID of the shader variable that contains the UV buffer array (u, v)
		GLuint getIDVertecesUVs() const;
		// Gets the ID of the shader variable that contains the normal buffer array (x, y, z)
		GLuint getIDVertecesNormals() const;
		// Gets a flag indicating whether the shader requires that both sides of the polygons be rendered
		bool getBothSide() const;

		// Allows to set the parameters related to the lights, to be able to render the following models
		// using those lights
		// @param [in] Lights - Lights to consider in the rendering of future models
		virtual void SetSceneLights(const std::vector<Light*>& Lights) abstract;

		// Set the ambient light in the scene and the next models to be rendered
		// @NOTE: It is required that the statement has been executed to the call of this method:
		// glUseProgram (ModelShader-> GetShaderID ());
		virtual void SetAmbientLight(const glm::vec3& L) abstract;

		// Set the necessary properties for the indicated material
		// @param [in] M - Material to be set
		// @NOTE: It is required that the statement has been executed to the call of this method:
		// glUseProgram (ModelShader-> GetShaderID ());
		virtual void SetMaterial(const Material* M) abstract;

		// Set the shader variables for the camera
		// @param [in] ViewMatix - Matrix of sight
		// @param [in] ProjectionMatrix - Projection of the gaming world
		// @NOTE: It is required that the statement has been executed to the call of this method:
		// glUseProgram (ModelShader-> GetShaderID ());
		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) abstract;

		// Allows you to set the parameters of the object to be rendered
		// @param [in] P - Parameters for the shader (can be null if the shader does not need parameters)
		// @param [in] ModelMatrix - Model Matrix
		// @NOTE 1: You must use the two methods SetMaterial () and SetMesh () before calling this method
		// It is optional to call the light methods SetSceneLights () and SetAmbientLight ()
		// @NOTE 2: It is required that the instruction has been executed to the call of this method:
		// glUseProgram (ModelShader-> GetShaderID ());
		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) abstract;
};

