#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\constants.hpp>
#include "InputState.h"
#include <GLFW\glfw3.h>

#include "DEBUG.h"

#include "PostProcessShaderParams.h"

/*
Camera::Camera(unsigned int ID, Scene* Scene, MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height)
{
	//TODO: anche la camera deve essere tattata come attori in InsertNewCamera(Camera* C)

	//Inizializzazione camera:
	position = glm::vec3(0, 0, 0);
	horizontalAngle = 0.0f;
	verticalAngle = 0.0f;
	speed = 5.0f;
	mouseSpeed = 0.005f;
	faceCulling = FaceCulling::FaceCulling_Disabled;
	coefficienteVelocitaCamera = 1.0f;


	//Limiti movimento visuale:
	//Impedisco alla camera di capovolgersi
	minVerticalAngle = -glm::pi<float>() / 2.f;
	maxVerticalAngle = glm::pi<float>() / 2.f;

	//Non limito la parte orizzontale
	minHorizontalAngle = 0.f;
	maxHorizontalAngle = 0.f;

	setProjectionMatrix(INITIAL_FOV, 4.f / 3.f, 0.1f, 1000.f); //Imposto la Projection matrix di default

	focused = false;
	frustumCulling = true;

	//Post process:
	idPostProcessEffectsCounter = 1;
	idFrameBuffer = 0;
	idDepthTexture = 0;

	modeOffset = ModeOffset;
	measureOffset = glm::vec2(X, Y);
	modeSize = ModeSize;
	measureSize = glm::vec2(Width, Height);

	//UpdateFrameBuffer();
}
*/

Camera::Camera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height)
{
	//Inizializzazione camera:
	position = glm::vec3(0, 0, 0);
	horizontalAngle = 0.0f;
	verticalAngle = 0.0f;
	speed = 5.0f;
	mouseSpeed = 0.005f;
	faceCulling = FaceCulling::FaceCulling_Disabled;
	coefficienteVelocitaCamera = 1.0f;


	//Limiti movimento visuale:
	//Impedisco alla camera di capovolgersi
	minVerticalAngle = -glm::pi<float>() / 2.f;
	maxVerticalAngle = glm::pi<float>() / 2.f;

	//Non limito la parte orizzontale
	minHorizontalAngle = 0.f;
	maxHorizontalAngle = 0.f;

	setProjectionMatrix(INITIAL_FOV, 4.f / 3.f, 0.1f, 1000.f); //Imposto la Projection matrix di default

	focused = false;
	frustumCulling = true;

	//Post process:
	idPostProcessEffectsCounter = 1;
	idFrameBuffer = 0;
	idDepthTexture = 0;

	modeOffset = ModeOffset;
	measureOffset = glm::vec2(X, Y);
	modeSize = ModeSize;
	measureSize = glm::vec2(Width, Height);

	//UpdateFrameBuffer();
}

Camera::~Camera()
{
}


void Camera::Update(float ElapsedTime)
{
	if (focused)
	{
		int cameraWidHalf = offset.x + size.x / 2;
		int cameraHeiHalf = offset.y + size.y / 2;

		Point2 cursorPos = getInputState()->getCursorPosition();

		// Reset mouse position for next frame
		CenterCursor();

		// Compute new orientation
		horizontalAngle += mouseSpeed * (float)(cameraWidHalf - cursorPos.x);
		verticalAngle += mouseSpeed * (float)(cameraHeiHalf - cursorPos.y);

		//Per la limitazione della camera:
		if(maxHorizontalAngle != 0.f) //Controllo se si vuole limitare l'angolo
			horizontalAngle = glm::min(horizontalAngle, maxHorizontalAngle);
		if (minHorizontalAngle != 0.f) //Controllo se si vuole limitare l'angolo
			horizontalAngle = glm::max(horizontalAngle, minHorizontalAngle);
		if (maxVerticalAngle != 0.f) //Controllo se si vuole limitare l'angolo
			verticalAngle = glm::min(verticalAngle, maxVerticalAngle);
		if (minVerticalAngle != 0.f) //Controllo se si vuole limitare l'angolo
			verticalAngle = glm::max(verticalAngle, minVerticalAngle);
		// Direction : Spherical coordinates to Cartesian coordinates conversion
		direction = glm::vec3(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
			);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
			);

		// Up vector
		glm::vec3 up = glm::cross(right, direction);

		// Muovi avanti
		if (getInputState()->IsKeyPressed(GLFW_KEY_W))
			position += direction * ElapsedTime * speed * coefficienteVelocitaCamera;
		else if (getInputState()->IsKeyPressed(GLFW_KEY_S)) // Muovi indietro
			position -= direction * ElapsedTime * speed * coefficienteVelocitaCamera;

		// Muovi destra
		if (getInputState()->IsKeyPressed(GLFW_KEY_D))
			position += right * ElapsedTime * speed * coefficienteVelocitaCamera;
		else if (getInputState()->IsKeyPressed(GLFW_KEY_A))
			position -= right * ElapsedTime * speed * coefficienteVelocitaCamera;

		// Muoversu su
		if (getInputState()->IsKeyPressed(GLFW_KEY_SPACE))
			position += up * ElapsedTime * speed * coefficienteVelocitaCamera;

		// Muoversu giu
		if (getInputState()->IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
			position -= up * ElapsedTime * speed * coefficienteVelocitaCamera;


		// Camera matrix
		viewMatrix = glm::lookAt(
			position,				// Camera is here
			position + direction,	// and looks here : at the same position, plus "direction"
			up						// Head is up (set to 0,-1,0 to look upside-down)
			);

		cameraMatrix = projectionMatrix * viewMatrix; //Calcolo la matrice della camera
	}
}

PostProcessEffect* Camera::AddPostProcessEffect(const PostProcessShader * S, PostProcessShaderParams * P)
{
	PostProcessEffect* eff = new PostProcessEffect(idPostProcessEffectsCounter, this, S, P);
	postProcessEffects.push_back(eff);
	idPostProcessEffectsCounter++;

	return eff;
}

int Camera::FindPostProcessEffect(int ID)
{
	int i = 0;
	while (i < postProcessEffects.size() && postProcessEffects[i]->getID() != ID)
		i++;

	if (i == postProcessEffects.size())
		return -1;
	else
		return i;
}

void Camera::RemovePostProcessEffect(int ID)
{
	int pos = FindPostProcessEffect(ID);
	if (pos == -1)
		ASSERT(false, "Effect not found");
	else
	{
		delete postProcessEffects[pos]->getPostProcessShaderParams(); //Elimino eventuali parametri
		delete postProcessEffects[pos]; //Rilascio la memoria dell'oggetto
		postProcessEffects.erase(postProcessEffects.begin() + pos); //Elimino l'effetto
	}
}

const std::vector<PostProcessEffect*>* Camera::getPostProcessEffects() const
{
	return &postProcessEffects;
}

void Camera::changePostProcessRenderTexture(int Index) const
{
	ASSERT(Index == 0 || Index == 1, "Camera::changePostProcessRenderTexture can change between two textures (IDs: 0 and 1)");
	glDrawBuffer(GL_COLOR_ATTACHMENT0 + Index); //Imposto dove andare a renderizzare il buffer
}

void Camera::setProjectionMatrix(const float& FovY, const float& AspectRatio, const float& ZNear, const float& ZFar)
{
	fovY = FovY;
	aspectRatio = AspectRatio;
	zNear = ZNear;
	zFar = ZFar;

	projectionMatrix = glm::perspective(fovY, aspectRatio, zNear, zFar);
	cameraMatrix = projectionMatrix * viewMatrix; //Aggiorno la matrice della camera (altrimenti bisognerebbe aspettare il prossimo Update)
}

const glm::mat4& Camera::getCameraMatrix() const
{
	return cameraMatrix;
}

const glm::mat4 & Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

const glm::mat4 & Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Point2 & Camera::getOffset() const
{
	return offset;
}

const Point2 & Camera::getSize() const
{
	return size;
}

const bool & Camera::isFocus() const
{
	return focused;
}

void Camera::setFrustumCulling(const bool & B)
{
	frustumCulling = B;
}

const bool & Camera::getFrustumCulling() const
{
	return frustumCulling;
}

const FaceCulling & Camera::getFaceCulling() const
{
	return faceCulling;
}

void Camera::setFaceCulling(const FaceCulling & F)
{
	faceCulling = F;
}

void Camera::setPosition(const glm::vec3 & P)
{
	position = P;
}

const glm::vec3& Camera::getPosition() const
{
	return position;
}

GLuint Camera::getFrameBufferID() const
{
	return idFrameBuffer;
}

GLuint Camera::getRenderedTextureID(int Index) const
{
	return idRenderTextures[Index];
}

GLuint Camera::getDepthTextureID() const
{
	return idDepthTexture;
}

void Camera::setMaxHorizontalAngle(float A)
{
	maxHorizontalAngle = A;
}

void Camera::setMinHorizontalAngle(float A)
{
	minHorizontalAngle = A;
}

void Camera::setMaxVerticalAngle(float A)
{
	maxVerticalAngle = A;
}

void Camera::setMinVerticalAngle(float A)
{
	minVerticalAngle = A;
}

float Camera::getMaxHorizontalAngle()
{
	return maxHorizontalAngle;
}

float Camera::getMinHorizontalAngle()
{
	return minHorizontalAngle;
}

float Camera::getMaxVerticalAngle()
{
	return maxVerticalAngle;
}

float Camera::getMinVerticalAngle()
{
	return minVerticalAngle;
}

void Camera::OnScreenReSize(size_t NewWidth, size_t NewHeight)
{
	Point2 windowSize(NewWidth, NewHeight);
	
	//Aggiorno la dimensione della camera
	offset = TransformToPixel(modeOffset, measureOffset, windowSize);
	size = TransformToPixel(modeSize, measureSize, windowSize);
	
	UpdateRatio(); //Aggiorno il valore dell'aspect ratio
	UpdateFrameBuffer(); //Aggiorno il frame buffer
	if(focused) //Centro il cursore solamente se la camera è in focus
		CenterCursor();
}

void Camera::Focus()
{
	focused = true;
	getInputState()->setCursorMode(IE_CursorMode::IE_CursorMode_Disabled);
	CenterCursor(); //Centro il cursore all'interno della camera
}

void Camera::Unfocus()
{
	focused = false;
	getInputState()->setCursorMode(IE_CursorMode::IE_CursorMode_Normal);
}

void Camera::SwitchFocus()
{
	if (focused)
		Unfocus();
	else
		Focus();
}

Point2 Camera::TransformToPixel(const MeasureMode & Mode, const glm::vec2 & Measure, const Point2 & WindowSize)
{
	switch (Mode)
	{
	case MeasureMode::MeasureMode_Constant: return Point2((int)Measure.x, (int)Measure.y);
	case MeasureMode::MeasureMode_Rate: return Point2((int)(Measure.x * WindowSize.x), (int)(Measure.y * WindowSize.y));

	default: 
		ASSERT(false, "Case not known"); 
		return Point2(); //Caso di errore e si desidera continuare
	}
}

void Camera::CenterCursor()
{
	getInputState()->setCursorPosition(offset.x + size.x / 2, offset.y + size.y / 2);
}

void Camera::UpdateRatio()
{
	//Ri-creo la matrice delle proiezioni mutando solamente l'aspect ratio
	setProjectionMatrix(fovY, (float)size.x / (float)size.y, zNear, zFar);
}

void Camera::UpdateFrameBuffer()
{
	//Elimino l'eventuale depth buffer memorizzato:
	glDeleteFramebuffers(1, &idFrameBuffer);
	glDeleteRenderbuffers(1, &depthRenderBuffer);
	glDeleteTextures(2, idRenderTextures);
	glDeleteTextures(1, &idDepthTexture);

	//Genero il frame buffer
	glGenFramebuffers(1, &idFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, idFrameBuffer);

	//Texture dove si va a renderizzare:
	glGenTextures(2, idRenderTextures);

	glBindTexture(GL_TEXTURE_2D, idRenderTextures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, idRenderTextures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// The depth buffer
	glGenRenderbuffers(1, &depthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
	
	// Alternative : Depth texture. Slower, but you can sample it later in your shader
	glGenTextures(1, &idDepthTexture);
	glBindTexture(GL_TEXTURE_2D, idDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, idRenderTextures[0], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, idRenderTextures[1], 0);

	// Depth texture alternative : 
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, idDepthTexture, 0);


	// Set the list of draw buffers.
	glDrawBuffer(GL_COLOR_ATTACHMENT0);

	// Always check that our framebuffer is ok
	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Faild to inizialize frame buffer for the camera");

	glBindFramebuffer(GL_FRAMEBUFFER, 0); //Setto per sicurezza come destinazione di rendering lo schermo
}
