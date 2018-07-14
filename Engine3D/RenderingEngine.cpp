#include "RenderingEngine.h"


#include "DEBUG.h"

#include <vector>
#include "Actor.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "Frustum.h"
#include "InputEngine.h"
#include "Skybox.h"
#include "PostProcessShader.h"
#include "PostProcessShaderParams.h"
#include "Rectangle.h"
#include "ModelShader.h"

#include "Font.h"
#include "SpriteFont.h"
#include <glm\gtc\matrix_transform.hpp>

#include "CommonConstants.h"

#ifdef _DEBUG
/*
	#include "ColorShader.h"
	ColorShader shaderColorDebug; // Shader used to debug
	GLuint idBuff_BoxFrustum; // Frustum buffer id (to view the video frustum box)
	#define SIZE_BUFF_LINES_BOX (72 * 4) // Size in bytes of the array containing the coordinates of the lines for the box
*/
#endif
	
GLuint RenderingEngine::idBuffUnitQuad = 0;

// Buffer containing a square of side 2, positioned on the origin
// the square is made up of two separate triangles
GLfloat bufferUnitVerteces[] =
{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	1.0f,  1.0f, 0.0f,
};


RenderingEngine::RenderingEngine()
{
}


RenderingEngine::~RenderingEngine()
{

}


void RenderingEngine::Inizialize()
{
	// Set the background color
	setBackgroundColor(glm::vec4(0, 0, 1, 0));

	// Enable depth test:
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); // Depth test to be performed: I accept the new pixel (obtained from the fragment-shader) if it is closer than the one already stored

	if (idBuffUnitQuad == 0) // Check if the buffer has been initialized previously
	{
		// I generate the buffer
		glGenBuffers(1, &idBuffUnitQuad);
		glBindBuffer(GL_ARRAY_BUFFER, idBuffUnitQuad);
		glBufferData(GL_ARRAY_BUFFER, sizeof(bufferUnitVerteces), bufferUnitVerteces, GL_STREAM_DRAW);
	}

	// Load the shader for switching from framebuffer to screen
	postProcess_final.LoadShader("PostProcess_Common.vert.glsl", "Texture.frag.glsl");
	// Load the shader to render the skybox
	skyboxShader.LoadShader("Skybox.vert.glsl", "Skybox.frag.glsl");


	// For the interface design
	draw2d.Inizialize();

#ifdef _DEBUG
/*
	shaderColorDebug.LoadShader("VertecesOnly.vert.glsl", "Color.frag.glsl");

	// I generate the debug buffer for the frutum box
	glGenBuffers(1, &idBuff_BoxFrustum);
	glBindBuffer(GL_ARRAY_BUFFER, idBuff_BoxFrustum);
	glBufferData(GL_ARRAY_BUFFER, SIZE_BUFF_LINES_BOX, nullptr, GL_STREAM_DRAW);
*/
#endif
}

void RenderingEngine::WindowResized(int Width, int Height)
{
	draw2d.SetWindowSize(Width, Height);
}

void RenderingEngine::setBackgroundColor(const glm::vec4& C)
{
	backgroundColor = C;
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
}

void RenderingEngine::EnableArraysShader(const ModelShader* S)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	// Check if the shader supports / requires UV and / or normal
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	glEnableVertexAttribArray(idCord);
	if (uvs) // Disabled only if the UVs are supported / requested by the shader
		glEnableVertexAttribArray(idUV);
	if (normals) // Disable only if the normals are supported / requested by the shader
		glEnableVertexAttribArray(idNorm);
}

void RenderingEngine::SetArraysShader(const ModelShader* S, const Mesh * M)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	// Check if the shader supports / requires UV and / or normal
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	// 1rst attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, M->getIDBuffVerteces());
	glVertexAttribPointer(
		idCord,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	if (uvs) // Check if the shader supports / requires UV
	{
		// 2nd attribute buffer: UVs
		glBindBuffer(GL_ARRAY_BUFFER, M->getIDBuffUV());
		glVertexAttribPointer(
			idUV,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);
	}

	if (normals) // Check if the shader supports / requires normal
	{
		// 3nd attribute buffer: Normals
		glBindBuffer(GL_ARRAY_BUFFER, M->getIDBuffNormals());
		glVertexAttribPointer(
			idNorm,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);
	}
}

void RenderingEngine::DisableArrayShader(const ModelShader* S)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	// Check if the shader supports / requires UV and / or normal
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	glDisableVertexAttribArray(idCord);
	if (uvs) // Disabled only if the UVs are supported / requested by the shader
		glDisableVertexAttribArray(idUV);
	if (normals) // Disable only if the normals are supported / requested by the shader
		glDisableVertexAttribArray(idNorm);
}

void RenderingEngine::RenderScene(Scene& S)
{
	// I order the actors to render:
	// TIME_NOW ();
	S.SortActors();
	// TIME_POP ("Sort time:");

	const Point2 windowSize = S.getLastInputState()->getWindowSize();

	// I get the series of items of the scene to be rendered
	const std::vector<Actor*>* actors = S.getActors();
	MapIterator<unsigned int, Camera*> cam = S.getCameras();
	MapIterator<unsigned int, Light*> lig = S.getLigths();


	Frustum frustum; // Class used to maintain the actors' frustrum in the scene

	// --- ROOMS ---
	while(cam.hasNext()) // Cycle for the rooms
	{
		const Camera* camera = cam.next(); // Pointer to the current room

		ASSERT(camera != nullptr, "Camera cannot be null");

		const Point2 o = camera->getOffset();
		const Point2 s = camera->getSize();
		Rectangle cameraPortion(o.x, windowSize.y - (o.y + s.y), s.x, s.y); // I get the portion of room used by the room
		const bool frustumCulling = camera->getFrustumCulling(); // Indicates whether the frustum culling is enabled by the camera

		glBindFramebuffer(GL_FRAMEBUFFER, camera->getFrameBufferID()); // I use the frame buffer of the camera
		camera->changePostProcessRenderTexture(0); // Always set as the first texture on which to render the first (number 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // I clean the frame buffer
		glViewport(cameraPortion.x, cameraPortion.y, cameraPortion.width, cameraPortion.height); // Render the camera in its position (inverting the Y axis)

		
		RenderSkybox(S.getSkyBox(), *camera); // I render the skybox if present, for this room

		const bool cameraCullFace = camera->getFaceCulling() != FaceCulling::FaceCulling_Disabled; // Indicates whether face culling is activated by the camera
		bool cullFace = cameraCullFace; // Current state of the culling of the faces
		// For face culling set by the camera:
		if (cullFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(camera->getFaceCulling()); // I set the desired mode from the camera
		}
		else
			glDisable(GL_CULL_FACE);

		frustum.setPlanes(camera->getCameraMatrix()); // Set the clipping plans for the frustrum

		// --- LIGHTS ---
		std::vector<Light*> activeLights; // Vector for lights to render
		// Cycle to eliminate the lights off or too far
		while (lig.hasNext())
		{
			Light* l = lig.next();
			if (l->state && frustum.TestView(glm::vec3(l->position), l->getClippingRadius())) // If turned on and in the frustum, I add the light in the list
				activeLights.push_back(l);
		}


		info.renderedActors = 0; // Counter for the number of actors rendered
		info.renderedTriangles = 0; // Counter for the rendered triangles
		const Actor* lastActor = nullptr; // Last actor rendered
		// ---- ACTORS -----
		for (int i = 0; i < actors->size(); i++) // Loop for rendering actors
		{
			const Actor* a = (*actors)[i];
			Box* b = a->getModel()->getMesh()->getFrustumBox() * a->getModelMatrix();

			// Check that the frustum culling is enabled by the camera, and in this case text if the actor is in the frustum
			// atrimenti senza frustum, I always draw the actor
			if (!frustumCulling || frustum.TestView(b))
			{
				info.renderedActors++; // Counter actors rendered

				const Model* m = a->getModel();
				const Material* mat = m->getMaterial();
				ModelShader* s = mat->getShader();

				info.renderedTriangles += m->getMesh()->getVertecesDraw() / 3;

				// Case is the first actor to render or if you have changed shader for rendering
				if (lastActor == nullptr || lastActor->getModel()->getMaterial()->getShader()->getIDShader() != s->getIDShader())
				{
					// I close the attributes for the sahder used previously to render the last actor (if there was a previous actor)
					if(lastActor != nullptr)
						DisableArrayShader(lastActor->getModel()->getMaterial()->getShader());

					// Enables / disables face culling based on the needs of the shader
					if (s->getBothSide()) // In case the shader requires that all the faces be rendered
					{
						if (cullFace)
						{
							glDisable(GL_CULL_FACE);
							cullFace = false;
						}
					}
					else
					{
						if (!cullFace)
						{
							glEnable(GL_CULL_FACE);
							cullFace = true;
						}
					}


					// Set the global attributes for the new shader:
					glUseProgram(s->getIDShader());
					s->SetSceneLights(activeLights);
					s->SetAmbientLight(S.getAmbientLight());
					s->SetCameraParameters(camera->getViewMatrix(), camera->getProjectionMatrix());
					s->SetMaterial(a->getModel()->getMaterial());

					EnableArraysShader(s);
					SetArraysShader(s, a->getModel()->getMesh()); // Set the buffers for the model mesh
				}
				else
				{
					if (m->getMaterial() != lastActor->getModel()->getMaterial()) // Case has changed the material (including the texture)
						s->SetMaterial(a->getModel()->getMaterial()); // Set the attributes of the sahder for the new material

					if (m->getMesh() != lastActor->getModel()->getMesh()) // Case has changed the mesh
						SetArraysShader(s, m->getMesh()); // Set the sahder attributes for the new mesh
				}

				s->SetObjectParameters(a->getActorParameters(), a->getModelMatrix()); // Settings for the shader for this object
				glDrawArrays(GL_TRIANGLES, 0, m->getMesh()->getVertecesDraw()); // Mesh rendering

				/*
				#ifdef _DEBUG
				glDisable(GL_DEPTH_TEST);

				float arr[] =
				{
					// Lower face:
					b->v1.x, b->v1.y, b->v1.z,
					b->v2.x, b->v2.y, b->v2.z,

					b->v2.x, b->v2.y, b->v2.z,
					b->v3.x, b->v3.y, b->v3.z,

					b->v3.x, b->v3.y, b->v3.z,
					b->v4.x, b->v4.y, b->v4.z,

					b->v4.x, b->v4.y, b->v4.z,
					b->v1.x, b->v1.y, b->v1.z,

					// Upper face:
					b->v5.x, b->v5.y, b->v5.z,
					b->v6.x, b->v6.y, b->v6.z,

					b->v6.x, b->v6.y, b->v6.z,
					b->v7.x, b->v7.y, b->v7.z,

					b->v7.x, b->v7.y, b->v7.z,
					b->v8.x, b->v8.y, b->v8.z,

					b->v8.x, b->v8.y, b->v8.z,
					b->v5.x, b->v5.y, b->v5.z,

					// Connection between upper and lower face:
					b->v1.x, b->v1.y, b->v1.z,
					b->v5.x, b->v5.y, b->v5.z,

					b->v2.x, b->v2.y, b->v2.z,
					b->v6.x, b->v6.y, b->v6.z,

					b->v3.x, b->v3.y, b->v3.z,
					b->v7.x, b->v7.y, b->v7.z,

					b->v4.x, b->v4.y, b->v4.z,
					b->v8.x, b->v8.y, b->v8.z,
				};

				glBindBuffer(GL_ARRAY_BUFFER, idBuff_BoxFrustum);
				glBufferData(GL_ARRAY_BUFFER, SIZE_BUFF_LINES_BOX, nullptr, GL_STREAM_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arr), arr);

				glUseProgram(shaderColorDebug.getIDShader());
				shaderColorDebug.RenderLines(idBuff_BoxFrustum, glm::vec4(1, 0, 0, 1), glm::mat4(1), camera->getCameraMatrix(), (sizeof(arr) / sizeof(float)) / 3);

				glEnable(GL_DEPTH_TEST);
				#endif
				*/

				lastActor = a;
			}


			delete b; // Disable the box

		} // ACTORS

		if (!cullFace) // If face culling is deactivated: enable it
			glEnable(GL_CULL_FACE);

		if (lastActor != nullptr) // If at least one actor has been rendered
			DisableArrayShader(lastActor->getModel()->getMaterial()->getShader()); // Disable the shader arrays

		// I apply post-process effects
		ApplayPostRenderEffects(*camera, cameraPortion);

	} // ROOMS

	// I render the interface
	RenderUI(S);
}

const RenderingEngineInfo& RenderingEngine::getRenderingEngineInfo() const
{
	return info;
}

GLuint RenderingEngine::getIDBuffUnitQuad()
{
	return idBuffUnitQuad;
}

void RenderingEngine::RenderSkybox(const Skybox* S, const Camera& C)
{
	if (S != nullptr) // There is a skybox for the scene
	{
		// Disable the depth test for the skybox to give the impression that it is very distant
		glDisable(GL_DEPTH_TEST);
		// Since the zNear parameter supplied to the camera can be high, it is disabled the clipping of pixels too close or too far from the camera
		// to prevent pixels from being rendered (clipping disabled)
		// https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glEnable.xml
		glEnable(GL_DEPTH_CLAMP);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // Enable interpolation between the various faces (higher quality on the edges of the skybox)
		
		// I render the skybox:
		glUseProgram(skyboxShader.getIDShader());
		skyboxShader.RenderSkybox(S, C.getCameraMatrix(), C.getPosition());

		// Set the parameters as before:
		glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glDisable(GL_DEPTH_CLAMP);
		glEnable(GL_DEPTH_TEST);
	}
}

void RenderingEngine::ApplayPostRenderEffects(const Camera& C, const Rectangle& Portion)
{
	// Disable the depth test to prevent it from being used (written) during post processing operations
	// which would not make sense
	glDisable(GL_DEPTH_TEST);

	// Post process effects
	const std::vector<PostProcessEffect*>* effects = C.getPostProcessEffects();
	int p = 0;
	for (; p < effects->size(); p++) // Cycle for the application of post process effects
	{
		// I change textures alternately in order to render all post-process effects
		// This mathematical expression can be translated as:
		// if (p% 2 == 0)
		// camera.changePostProcessRenderTexture (1);
		// else
		// camera.changePostProcessRenderTexture (0);
		C.changePostProcessRenderTexture(1 - p % 2);
		glClear(GL_COLOR_BUFFER_BIT); // I clean the old texture
		PostProcessEffect* eff = (*effects)[p];

		// Default parameter settings:
		if (eff->getPostProcessShaderParams() != nullptr) // If there are any parameters
		{
			eff->getPostProcessShaderParams()->setResolution(glm::vec2(C.getSize().x, C.getSize().y));
		}

		glUseProgram(eff->getPostProcessShader()->getIDShader());
		eff->getPostProcessShader()->ApplayShader(idBuffUnitQuad, C.getRenderedTextureID(p % 2), C.getDepthTextureID(), eff->getPostProcessShaderParams());
	}

	// On-screen rendering
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(Portion.x, Portion.y, Portion.width, Portion.height); // Re-set of the view port
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(postProcess_final.getIDShader());
	postProcess_final.DrawFrame(idBuffUnitQuad, C.getRenderedTextureID(p % 2)); // I render the final frame

	glEnable(GL_DEPTH_TEST); // Re-enable the delpth test
}

void RenderingEngine::RenderUI(Scene & S)
{
	// Design the interface in 2D
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); // Enable transparency
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	// I have the interface elements
	const std::vector<UIElement*> uiElements = S.getUI().getUIElements();
	for (int i = 0; i < uiElements.size(); i++)
		uiElements[i]->DrawControl(&draw2d);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
