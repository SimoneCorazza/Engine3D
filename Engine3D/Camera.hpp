#pragma once


#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>

#include "ItemScene.hpp"
#include "Point2.hpp"
#include "PostProcessEffect.hpp"

class PostProcessShaderParams;
class PostProcessShader;

// Enumeration to indicate how a measure is interpreted
enum MeasureMode
{
	MeasureMode_Rate, // Indicates that the measure will be in percentage
	MeasureMode_Constant, // Indicates that the measure will be expressed in exact figures and will not have to change
};

// Enumeration to indicate if face culling is present and if so the mode
// the values ​​assumed if it is enabled coincide with those of OpenGL
enum FaceCulling : int
{
	FaceCulling_Disabled = 0, // Face culling disabled
	FaceCulling_Front = GL_FRONT, // Face culling enabled and set on the front of the face
	FaceCulling_Back = GL_BACK, // Face culling enabled and set on the back of the face
	FaceCulling_FrontAndBack = GL_FRONT_AND_BACK,  // Face culling enabled and set on the front of the face
};


// Class that represents the portion of the world viewed
class Camera : public ItemScene
{
	// Visual:
	glm::vec3 direction; // Direction of the camera
	glm::vec3 position; // Location of the camera
	float horizontalAngle; // Horizontal angle
	float verticalAngle; // Vertical angle

	// camera view limits:
	float maxHorizontalAngle; // Maximum angle (to the right) possible for the camera
	float minHorizontalAngle;  // Minimum angle (to the left) possible for the camera
	float maxVerticalAngle; // Maximum angle (upward) possible for the camera
	float minVerticalAngle;  // Minimum angle (downwards) possible for the camera

	// Initial Field of View
	#define INITIAL_FOV 45.0f
	
	float fovY; // Fov of the camera
	float aspectRatio; // Current ratio of the camera
	float zNear; // Minimum distance at which objects are rendered
	float zFar; // Maximum distance at which objects are rendered

	float speed;
	float mouseSpeed;

	float coefficienteVelocitaCamera;

	glm::mat4 viewMatrix; // View matrix obtained by the user through input devices
	glm::mat4 cameraMatrix; // Matrix of the chamber obtained by multiplying in order: the matrix of the projection with that of the view
	glm::mat4 projectionMatrix; // Projection matrix set by the user

	bool focused; // Indicates if the camera is selected and ready for input
	bool frustumCulling; // Indicates whether the frustum culling for the actors to be rendered is enabled for the camera
	FaceCulling faceCulling; // Indicates the face culling of the camera

	Point2 offset; // camera offset in pixels
	Point2 size; // camera size in pixels

	MeasureMode modeOffset; // How to deal with the offset measurement
	glm::vec2 measureOffset; // Measurement of the camera offset according to the pre-selected mode (pixel, percentage, ...)
	MeasureMode modeSize; // How to treat the size measurement
	glm::vec2 measureSize;  // Measurement of the size of the camera according to the pre-selected mode (pixel, percentage, ...)

	// - POST PROCESS EFFECTS

	GLuint idFrameBuffer; // camera framebuffer
	// Ids of the texture connected to the frame buffer, where the result of the rendering operation is inserted,
	// there are two to be able to exchange in turn to be able to apply more post-process effects
	GLuint idRenderTextures[2];
	GLuint idDepthTexture; // ID of the texture connected to the frame buffer, where the depth is inserted

	GLuint depthRenderBuffer; // Depth buffer inserted in the framebuffer

	unsigned int idPostProcessEffectsCounter; // Counter for generating the effects of prost prost effects
	std::vector<PostProcessEffect*> postProcessEffects; // Post-rendering effects of the camera

	public:
		// Instant a camra
		// @param [in] ID - ID of the camera
		// @param [in] Scene - Scene containing the camera
		// @param [in] ModeOffset - Desired measurement mode for camera offset
		// @param [in] X - Desired measurement mode for the camera size
		// @param [in] Y - Desired measurement mode for camera size
		// @param [in] ModeSize - Desired measurement mode for the camera size
		// @param [in] Width - Length of the camera relative to the window (using the mode indicated above)
		// @param [in] Height - camera height compared to the window (using the mode indicated above)
		// Camera (unsigned int ID, Scene * Scene, MeasureMode ModeOffset, X float, Y float, MeasureMode ModeSize, float Width, float Height);

		// Instant a camra
		// @param [in] ModeOffset - Desired measurement mode for camera offset
		// @param [in] X - Desired measurement mode for the camera size
		// @param [in] Y - Desired measurement mode for camera size
		// @param [in] ModeSize - Desired measurement mode for the camera size
		// @param [in] Width - Length of the camera relative to the window (using the mode indicated above)
		// @param [in] Height - camera height compared to the window (using the mode indicated above)
		Camera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height);
		~Camera();


	public:


		// It allows you to update the camera interface
		// NOTE: reserved for the SCENE class
		void Update(float ElapsedTime);

		// Method that allows you to upgrade the camera to the size change of the game window
		// NOTE: reserved for the SCENE class
		void OnScreenReSize(size_t NewWidth, size_t NewHeight);

		// Enable the camera to input
		void Focus();
		// It allows to disable the camera to the inputs
		void Unfocus();
		// It allows you to invert the focus status of the camera
		void SwitchFocus();

		// - Post-processing effects

		// Adds a post process effect
		// @param [in] A - Shader to use as an effect
		// @param [in] P - Parameters for the effect shader (they can be NULL, if the shader supports it)
		// @return Effect proved
		PostProcessEffect* AddPostProcessEffect(const PostProcessShader* S, PostProcessShaderParams* P);

		// Allows you to remove a post process effect from the list
		void RemovePostProcessEffect(int ID);

		// Gets the post process effects of the camera
		const std::vector<PostProcessEffect*>* getPostProcessEffects() const;

		// Change the textrue where to render the frame buffer
		// @param [in] Index - Indicates the texture to render: 0 or 1
		void changePostProcessRenderTexture(int Index) const;

		// GET and SET

		// Set the projection matrix
		void setProjectionMatrix(const float& FovY, const float& AspectRatio, const float& ZNear, const float& ZFar);

		// Gets the matrix of the chamber obtained from the product of the projection matrix with that of the view
		const glm::mat4& getCameraMatrix() const;

		// Gets the matrix of the projection of the camera
		const glm::mat4& getProjectionMatrix() const;

		// Gets the matrix of the camera view
		const glm::mat4& getViewMatrix() const;

		// Gets the position of the camera angle in the window
		const Point2& getOffset() const;
		// Gets the size of the camera in the window
		const Point2& getSize() const;

		// Gets a flag indicating if the camera is enabled (it receives the inputs)
		const bool& isFocus() const;

		// Sets a flag indicating whether the camera enables frustum culling
		void setFrustumCulling(const bool& B);
		// Gets a flag indicating whether the camera enables frustum culling
		const bool& getFrustumCulling() const;

		// Gets the face culling of the camera
		const FaceCulling& getFaceCulling() const;
		// Set the face culling of the camera
		void setFaceCulling(const FaceCulling& F);

		// Set the position of the camera
		void setPosition(const glm::vec3& P);
		// Gets the position of the camera
		const glm::vec3& getPosition() const;

		// Set the speed of the camera
		void setSpeed(float speed);
		// Gets the speed of the camera
		const float getSpeed() const;

		// Frame buffer:

		// Gets the framebuffer id of the camera
		GLuint getFrameBufferID() const;
		// Gets the id of the rendered frame texture
		// @param [in] Index - Index of the desired current frame texture (0 or 1)
		GLuint getRenderedTextureID(int Index) const;
		// Gets the id of the texture of the scene depth
		GLuint getDepthTextureID() const;

		// Visual movement limits:

		// Set the maximum angle (to the right) possible for the camera
		// the value must be> 0 or = 0 to not give limits
		// PI / 2 = look to the right
		void setMaxHorizontalAngle(float A);
		// Set minimum angle (to the left) possible for the camera
		// the value must be <0 or = 0 to not give limits
		// PI / 2 = look to the left
		void setMinHorizontalAngle(float A);
		// Set maximum angle (upward) possible for the camera
		// the value must be> 0 or = 0 to not give limits
		// PI / 2 = look upwards
		void setMaxVerticalAngle(float A);
		// Set minimum angle (down) possible for the camera
		// the value must be <0 or = 0 to not give limits
		// PI / 2 = look down
		void setMinVerticalAngle(float A);

		// Gets the maximum angle (to the right) possible for the camera
		float getMaxHorizontalAngle();
		// Gets the minimum angle (to the left) possible for the camera
		float getMinHorizontalAngle();
		// Get maximum angle (upward) possible for the camera
		float getMaxVerticalAngle();
		// It obtains minimum angle (downwards) possible for the camera
		float getMinVerticalAngle();

	private:

		// Gets the position occupied by the effect with the indicated id (if not present returns -1)
		int FindPostProcessEffect(int ID);

		// Allows you to transform a measurement from its pixel mode
		// @param [in] Mode - Measurement mode
		// @param [in] Measure - Measure to transform
		// @param [in] Window Size - Window size in pixels
		Point2 static TransformToPixel(const MeasureMode& Mode, const glm::vec2& Measure, const Point2& WindowSize);

		// Allows you to place the cursor in the middle of the camera
		void CenterCursor();

		// It allows to update the ratio of projection matrix (and consequently to the matrix camera)
		// according to the size of the screen
		void UpdateRatio();

		// Update the frame buffer of the camera
		void UpdateFrameBuffer();
};

