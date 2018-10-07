#include "SceneTest.hpp"

#include "Engine.hpp"

#include "Texture2D.hpp"
#include "TextureCube.hpp"
#include "Model.hpp"
#include "Mesh.hpp"
#include "StandardShader.hpp"
#include "Material.hpp"
#include "Actor.hpp"


#include "InputEngine.hpp"
#include "Point2.hpp"
#include <GLFW\glfw3.h>

#include "Utility_FileSystem.hpp"

#include "PostProcessShaderParams.hpp"
#include "BlackAndWhitePostProcessShader.hpp"
#include "BlurPostProcessShader.hpp"
#include "LightTextureShader.hpp"
#include "DepthPostProcessShader.hpp"
#include "LiftTriShader.hpp"


#include "DEBUG.hpp"

#include "Utility_Arrays.hpp"
#include "InputState.hpp"

#include "TextBox.hpp"

#include "MyActor.hpp"

#define GLM_FORCE_RADIANS



SceneTest::SceneTest()
{
}


SceneTest::~SceneTest()
{
}



#define NUM_ACT_X 1
#define NUM_ACT_Y 100
#define NUM_ACT_Z 100

Actor* actor[NUM_ACT_X][NUM_ACT_Y][NUM_ACT_Z];
TextBox* txt = nullptr;

void SceneTest::InizializeScene()
{
	camera = InsertNewCamera(MeasureMode::MeasureMode_Rate, .0f, .0f, MeasureMode::MeasureMode_Rate, 1.f, 1.f);
	camera->Focus();
	camera->setFaceCulling(FaceCulling::FaceCulling_Back);
	camera->setFrustumCulling(true);
	camera->setProjectionMatrix(45.f, 4.f / 3.f, .6f, 500.f);

	StandardShader* standardShader = new StandardShader();
	standardShader->LoadShader("Standard.vert.glsl", "Texture.frag.glsl");

	LightTextureShader* lightTexture = new LightTextureShader();
	lightTexture->LoadShader("LightTexture.vert.glsl", "LightTexture.frag.glsl");

	LiftTriShader* liftTriShader = new LiftTriShader();
	liftTriShader->LoadShader("LiftTri.vert.glsl", "Texture.frag.glsl");


	BlackAndWhitePostProcessShader* blackAndWhite = new BlackAndWhitePostProcessShader();
	blackAndWhite->LoadShader("PostProcess_Common.vert.glsl", "PostProcess_BlackWhite.frag.glsl");

	BlurPostProcessShader* postBlur = new BlurPostProcessShader();
	postBlur->LoadShader("PostProcess_Common.vert.glsl", "PostProcess_Blur.frag.glsl");

	DepthPostProcessShader* postDepth = new DepthPostProcessShader();
	postDepth->LoadShader("PostProcess_Common.vert.glsl", "PostProcess_Depth.frag.glsl");

	ambientLight = glm::vec3(0.5f, 0.5f, 0.5f);

	// camera-> AddPostProcessEffect (blackAndWhite, nullptr);
	// camera-> AddPostProcessEffect (postBlur, new PostProcessShaderParams ());
	// camera-> AddPostProcessEffect (postDepth, nullptr);

	TextureCube* texCube = TextureCube::NewTextureCube("Cubemap3.png", GL_RGB, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, true);
	// Model * modelSkyBox = new Model (meshSphere, new Material (standardShader, texSkybox));
	Skybox* box = new Skybox(Mesh::CubeInternal(glm::vec3(0, 0, 0), 1), texCube);
	InsertSkybox(box);

	Light* light0 = InsertNewLight();
	light0->position = glm::vec4(0.0, 2.0, 2.0, 1.0);
	light0->diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
	light0->specular = glm::vec4(1.0, 1.0, 1.0, 1.0);
	light0->constantAttenuation = 0;
	light0->linearAttenuation = 1;
	light0->quadraticAttenuation = 0;
	light0->spotCutoff = 180;
	light0->spotExponent = 0;
	light0->spotDirection = glm::vec3(0, 0, 0);

	Light* light1 = InsertNewLight();
	light1->position = glm::vec4(0.0, -3.0, 0.0, 1.0);
	light1->diffuse = glm::vec4(1.0, 1.0, 1.0, 1.0);
	light1->specular = glm::vec4(0.1, 0.1, 0.1, 1.0);
	light1->constantAttenuation = 0;
	light1->linearAttenuation = 1;
	light1->quadraticAttenuation = 0;
	light1->spotCutoff = 80;
	light1->spotExponent = 10;
	light1->spotDirection = glm::vec3(0, 1, 0);

	Texture2D* texture = Texture2D::NewTexture2D("bricks_wall.jpg", GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Texture2D* texture2 = Texture2D::NewTexture2D("world.jpg", GL_RGB, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, 4);
	Material* material = new Material(liftTriShader, texture);
	Material* world = new Material(liftTriShader, texture2);
	material->setAmbient(glm::vec3(0, 0, 0));
	
	Mesh* meshSphere = Mesh::Sphere(glm::vec3(), 1.f, 20, true, true);
	Mesh* meshCube = Mesh::LoadMSH("cube.msh");
	
	Model* sphere = new Model(meshSphere, world);
	Model* cube = new Model(meshCube, material);

	for (int x = 0; x < NUM_ACT_X; x++)
		for (int y = 0; y < NUM_ACT_Y; y++)
			for (int z = 0; z < NUM_ACT_Z; z++)
			{
				if ((z + x + y) % 2 == 0)
				{
					actor[x][y][z] = new MyActor();
					actor[x][y][z]->setModel(sphere);
				}
				else
				{
					actor[x][y][z] = new MyActor();
					actor[x][y][z]->setModel(cube);
				}
				actor[x][y][z]->setLocation(x * 2.5f, y * 3.f, z * 2.5f);
				InsertNewActor(actor[x][y][z]);
			}


	Font* fnt = new Font();
	fnt->Load("arial.ttf", 60);
	txt = new TextBox();
	txt->setArea(Rectangle(0, 0, 10, 20));
	txt->setFont(fnt);
	txt->setTextColor(glm::vec4(1, 0, 0, 1));
	getUI().Add(*txt);
}

void SceneTest::UpdateScene(const UpdateParameters& SceneUpdateParameters)
{
	if (getLastInputState()->IsKeyPressed(GLFW_KEY_ESCAPE))
		Terminate();
	else if (getLastInputState()->IsKeyDown(GLFW_KEY_F1))
		camera->SwitchFocus();

	std::string act = std::to_string(getRenderingEngineInfo().renderedActors);
	txt->setText(act + "\t " + std::to_string(1.0f / SceneUpdateParameters.getElapsedTime()));
}
