#include "RenderingEngine.hpp"


#include "DEBUG.hpp"

#include <vector>
#include "Actor.hpp"
#include "Scene.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Frustum.hpp"
#include "InputEngine.hpp"
#include "Skybox.hpp"
#include "PostProcessShader.hpp"
#include "PostProcessShaderParams.hpp"
#include "Rectangle.hpp"
#include "ModelShader.hpp"

#include "Font.hpp"
#include "SpriteFont.hpp"
#include <glm\gtc\matrix_transform.hpp>

#include "CommonConstants.hpp"
	
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

	// Check if the shader supports/requires UV and/or normal
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	glEnableVertexAttribArray(idCord);
	if (uvs) // Disabled only if the UVs are supported/requested by the shader
		glEnableVertexAttribArray(idUV);
	if (normals) // Disable only if the normals are supported/requested by the shader
		glEnableVertexAttribArray(idNorm);
}

void RenderingEngine::SetArraysShader(const ModelShader* S, const Mesh * M)
{
	GLuint idCord = S->getIDVertecesCoords();
	GLuint idUV = S->getIDVertecesUVs();
	GLuint idNorm = S->getIDVertecesNormals();

	// Check if the shader supports/requires UV and/or normal
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

	if (uvs) // Check if the shader supports/requires UV
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

	if (normals) // Check if the shader supports/requires normal
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

	// Check if the shader supports/requires UV and/or normal
	bool uvs = idUV != INVALID_BUFFER_ID;
	bool normals = idNorm != INVALID_BUFFER_ID;

	glDisableVertexAttribArray(idCord);
	if (uvs) // Disabled only if the UVs are supported/requested by the shader
		glDisableVertexAttribArray(idUV);
	if (normals) // Disable only if the normals are supported/requested by the shader
		glDisableVertexAttribArray(idNorm);
}

void RenderingEngine::RenderScene(Scene& S)
{
	// I order the actors to render:
	S.SortActors();

	const Point2 windowSize = S.getLastInputState()->getWindowSize();

	// I get the series of items of the scene to be rendered
	const std::vector<Actor*>* actors = S.getActors();
	MapIterator<unsigned int, Camera*> cam = S.getCameras();
	MapIterator<unsigned int, Light*> lig = S.getLigths();


	Frustum frustum; // Class used to maintain the actors' frustrum in the scene

	// --- CAMERA ---
	while(cam.hasNext()) // Cycle for the cameras
	{
		const Camera* camera = cam.next(); // Pointer to the current camera

		ASSERT(camera != nullptr, "Camera cannot be null");

		const Point2 o = camera->getOffset();
		const Point2 s = camera->getSize();
		Rectangle cameraPortion(o.x, windowSize.y - (o.y + s.y), s.x, s.y); // I get the portion of screen used by the camera
		const bool frustumCulling = camera->getFrustumCulling(); // Indicates whether the frustum culling is enabled by the camera

		glBindFramebuffer(GL_FRAMEBUFFER, camera->getFrameBufferID()); // I use the frame buffer of the camera
		camera->changePostProcessRenderTexture(0); // Always set as the first texture on which to render the first (number 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // I clean the frame buffer
		glViewport(cameraPortion.x, cameraPortion.y, cameraPortion.width, cameraPortion.height); // Render the camera in its position (inverting the Y axis)

		
		RenderSkybox(S.getSkyBox(), *camera); // I render the skybox if present, for this camera

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
		// Cycle to eliminate the lights turned off or too far
		while (lig.hasNext())
		{
			Light* l = lig.next();
			if (l->state && frustum.TestView(glm::vec3(l->position), l->getClippingRadius()))
				activeLights.push_back(l);
		}


		// ---- ACTORS -----
		info.renderedActors = 0; // Counter for the number of actors rendered
		info.renderedTriangles = 0; // Counter for the rendered triangles
		const Actor* lastActor = nullptr; // Last actor rendered
		// Loop for rendering actors
		for (int i = 0; i < actors->size(); i++)
		{
			const Actor* a = (*actors)[i];
			Box* b = a->getModel()->getMesh()->getFrustumBox() * a->getModelMatrix();

			// Check that the frustum culling is enabled by the camera, and in this case test if the actor is in the frustum
			// otherwise without frustum, I always draw the actor
			if (!frustumCulling || frustum.TestView(b))
			{
				info.renderedActors++;

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

					// Enables/disables face culling based on the needs of the shader
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

				lastActor = a;
			}


			delete b;

		} // ACTORS

		if (!cullFace) // If face culling is deactivated: enable it
			glEnable(GL_CULL_FACE);

		if (lastActor != nullptr) // If at least one actor has been rendered
			DisableArrayShader(lastActor->getModel()->getMaterial()->getShader()); // Disable the shader arrays

		// I apply post-process effects
		ApplayPostRenderEffects(*camera, cameraPortion);

	} // CAMERAS

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
	// There is a skybox for the scene
	if (S != nullptr)
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
