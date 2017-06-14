#include "Engine.h"
#include "SceneTest.h"

int main(int numArgs, char** args)
{
	Engine engine;
	engine.Inizialize();
	engine.CreateNewWindow("Engine3D", 640, 480);
	//glfwSwapInterval(0); //Non limita gli FPS
	SceneTest sceneTest;
	engine.StartGameLoop(&sceneTest);

    exit(EXIT_SUCCESS);
}

























/*
//Set the error callback
glfwSetErrorCallback(error_callback);


//Initialize GLFW
if (!glfwInit())
{
exit(EXIT_FAILURE);
}

//Set the GLFW window creation hints - these are optional
//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
//glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//glfwWindowHint(GLFW_SAMPLES, 4);


//Declare a window object
GLFWwindow* window;


//Create a window and create its OpenGL context
window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);

//If the window couldn't be created
if (!window)
{
fprintf( stderr, "Failed to open GLFW window.\n" );
glfwTerminate();
exit(EXIT_FAILURE);
}

//This function makes the context of the specified window current on the calling thread.
glfwMakeContextCurrent(window);

//Sets the key callback
glfwSetKeyCallback(window, key_callback);

//Initialize GLEW
GLenum err = glewInit();

//If GLEW hasn't initialized
if (err != GLEW_OK)
{
fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
return -1;
}

//Set a background color
glClearColor(0.0f, 0.0f, 1.0f, 0.0f);


// Enable depth test
glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
glDepthFunc(GL_LESS);

*/


/*

// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
1.0f, 1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f
};

// Two UV coordinatesfor each vertex. They were created withe Blender.
static const GLfloat g_uv_buffer_data[] = {
0.000059f, 1.0f - 0.000004f,
0.000103f, 1.0f - 0.336048f,
0.335973f, 1.0f - 0.335903f,
1.000023f, 1.0f - 0.000013f,
0.667979f, 1.0f - 0.335851f,
0.999958f, 1.0f - 0.336064f,
0.667979f, 1.0f - 0.335851f,
0.336024f, 1.0f - 0.671877f,
0.667969f, 1.0f - 0.671889f,
1.000023f, 1.0f - 0.000013f,
0.668104f, 1.0f - 0.000013f,
0.667979f, 1.0f - 0.335851f,
0.000059f, 1.0f - 0.000004f,
0.335973f, 1.0f - 0.335903f,
0.336098f, 1.0f - 0.000071f,
0.667979f, 1.0f - 0.335851f,
0.335973f, 1.0f - 0.335903f,
0.336024f, 1.0f - 0.671877f,
1.000004f, 1.0f - 0.671847f,
0.999958f, 1.0f - 0.336064f,
0.667979f, 1.0f - 0.335851f,
0.668104f, 1.0f - 0.000013f,
0.335973f, 1.0f - 0.335903f,
0.667979f, 1.0f - 0.335851f,
0.335973f, 1.0f - 0.335903f,
0.668104f, 1.0f - 0.000013f,
0.336098f, 1.0f - 0.000071f,
0.000103f, 1.0f - 0.336048f,
0.000004f, 1.0f - 0.671870f,
0.336024f, 1.0f - 0.671877f,
0.000103f, 1.0f - 0.336048f,
0.336024f, 1.0f - 0.671877f,
0.335973f, 1.0f - 0.335903f,
0.667969f, 1.0f - 0.671889f,
1.000004f, 1.0f - 0.671847f,
0.667979f, 1.0f - 0.335851f
};

Texture* Texture = &TextureLoader::LoadBMP("C:\\Develop\\OpenGL C++\\OpenGLProva2\\Debug\\Content\\Immagine.bmp");

StandardShader* standardShader = new StandardShader();
standardShader->CaricaShader("Standard.vert", "Texture.frag");

int numVertDraw = (sizeof(g_vertex_buffer_data) / sizeof(float)) / 3;
Mesh* mesh = &Mesh::Create(g_vertex_buffer_data, g_uv_buffer_data, numVertDraw);
Material* material = new Material(standardShader, Texture);
Model* model = new Model(mesh, material);

Camera camera;
camera.setWindow(window);

//glfwSwapInterval(0); //Non limita gli FPS


//Main Loop
do
{
// Clear the screen
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

camera.Update();

glUseProgram(standardShader->getIDShader());
//standardShader.RenderTriangles(Texture.getIDTexture(), vertexbuffer, uvbuffer, glm::mat4(1.0f), camera.getCameraMatrix(), 12 * 3);
standardShader->RenderModel(model, glm::mat4(1.0f), camera.getCameraMatrix());

glfwSwapBuffers(window);
glfwPollEvents();

}
while (!glfwWindowShouldClose(window));
*/