#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "PostProcess_Final.hpp"
#include "SkyboxShader.hpp"
#include "CheckTable.hpp"
#include "ModelShader.hpp"
#include "Draw2D.hpp"

#include "RenderingEngineInfo.hpp"

class Scene;
class Skybox;
class Camera;
struct Rectangle;

// Class that manages the rendering of the engine
class RenderingEngine
{
	glm::vec4 backgroundColor; // Clear color

	// - SKYBOX

	SkyboxShader skyboxShader;

	// - POST PROCESS

	PostProcess_Final postProcess_final; // Post process effect for the final transition from the frame buffer to the screen

	// --- INTERFACE

	Draw2D draw2d; // Class to render the various elements of the UI

	// - DEFAULT DATA

	// ID of the buffer containing a square of side 2, positioned on the origin
	// the square is made up of two separate triangles
	// Used for example by the vertex shader for post-render effects
	static GLuint idBuffUnitQuad;

	// - SUPPORT STRUCTURE
	// Support structures for rendering
	
	// - INFO ABOUT THE END ---

	RenderingEngineInfo info;


	public:
		RenderingEngine();
		~RenderingEngine();


	public:

		// It allows to initialize the rendering engine
		void Inizialize();

		// Method to indicate that the window has been resized
		// @param [in] Width - New window length in pixels
		// @param [in] Height - New window height in pixels
		void WindowResized(int Width, int Height);

		// Set the background color
		void setBackgroundColor(const glm::vec4& C);

		// It allows you to render the scene
		void RenderScene(Scene& S);
		
		// @return Information on the work of the engine
		const RenderingEngineInfo& getRenderingEngineInfo() const;

		// Gets the id of the buffer containing a square of side 2, positioned on the origin
		// the square is made up of two separate triangles
		static GLuint getIDBuffUnitQuad();

	private:

		// Render the skybox of the scene
		void RenderSkybox(const Skybox* S, const Camera& C);

		// Apply post-render effects to the camera and draw the resulting frame on the screen
		// @NOTE: We assume:
		// • that the scene for the data camera has already been rendered on the texture with ID 0
		// • that the camera FBO is still selected
		// FINAL NOTE: This method was only tested immediately after the data camera was rendered
		// @param [in] C - camera from which to render the post-process effects
		// @param [in] Portion - Screen portion reserved for the pixel camera
		void ApplayPostRenderEffects(const Camera& C, const Rectangle& Portion);

		// It allows to render the indicated scene
		// @param [in] S - Scene of which to design the interface
		void RenderUI(Scene& S);

		// Enables the variables / attributes for mesh buffers to be enabled
		// @param [in] S - Shader to set buffers
		void EnableArraysShader(const ModelShader* S);

		// Allows you to set the attributes of the mesh in the shader such as: vertices, uv and normal
		// (if requested by the shader)
		// @param [in] S - Shader to set mesh buffers
		// @param [in] M - Mesh to be put in the shader
		void SetArraysShader(const ModelShader* S, const Mesh* M);

		// Disables the variables / attributes for mesh buffers
		// @param [in] S - Shader to disable
		void DisableArrayShader(const ModelShader* S);
};

