/*
*
* 09 - Animación
*/

#include <iostream>
#include <stdlib.h>



// GLAD: Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator
// https://glad.dav1d.de/
#include <glad/glad.h>

// GLFW: https://www.glfw.org/
#include <GLFW/glfw3.h>

// GLM: OpenGL Math library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Model loading classes
#include <shader_m.h>
#include <camera.h>
#include <model.h>
#include <animatedmodel.h>
#include <material.h>
#include <light.h>
#include <cubemap.h>

#include <irrKlang.h>
using namespace irrklang;
#include "ChessGame.h"

float floorOffsetZ = 0.0f; // Variable para el desplazamiento del piso
float floorSpeed = 1.0f;   // Velocidad del movimiento (ajústala según necesites)

const float DOOR_PROXIMITY_DISTANCE = 3.0f; // Distancia para activar apertura


// Functions
bool Start();
bool Update();

// Definición de callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void RenderChess(Shader* shader, glm::mat4 model);
glm::vec3 ScreenToWorld(double xpos, double ypos, glm::mat4 projection, glm::mat4 view, float planeY);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void limitBox(float xMax, float xMin, float zMax, float zMin);
bool teleportCamera(float xMax, float xMin, float zMax, float zMin, glm::vec3 newPos);
bool reachBox(float xMax, float xMin, float zMax, float zMin);
bool isPlayerNearDoor(const glm::vec3& playerPosition, const glm::vec3& doorPosition, float threshold);


void cambio_escena();

// Gobals
GLFWwindow* window;

// Tamaño en pixeles de la ventana
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// Definición de cámara (posición en XYZ)
Camera camera(glm::vec3(3.0f, 2.0f, -3.0f));
Camera camera3rd(glm::vec3(0.0f, 0.0f, 0.0f));

// Controladores para el movimiento del mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Variables para la velocidad de reproducción
// de la animación
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float elapsedTime = 0.0f;

glm::vec3 position(0.0f, 0.0f, 0.0f);
glm::vec3 forwardView(0.0f, 0.0f, 1.0f);
float     trdpersonOffset = 1.5f;
float     scaleV = 0.025f;
float     rotateCharacter = 0.0f;
float	  door_offset = 0.0f;
float	  door_rotation = 0.0f;

float	  alturaTransEs = -3.0f;
bool	  cambiandoEscena = false;

// Shaders
Shader* mLightsShader;
Shader* proceduralShader;
Shader* wavesShader;
Shader* fresnelShader;

Shader* cubemapShader;
Shader* dynamicShader;

// Carga la información del modelo
Model* terrenos;
Model* monte;
Model* llanura_irregular;
Model* templos;
Model* puerta1;
Model* puerta2;


Model* salaInicial;

Model* AldeaVikinga;
Model* aguapueblo;
Model* Yucatas;
Model* EmbarcacionVik;
Model* aguaembarcacion;
Model* aguapueblo_2;

Model* CambioEscena;

// Modelos animados
AnimatedModel* character01;
AnimatedModel* character02;
AnimatedModel* character03;
AnimatedModel* character04;
AnimatedModel* caballo01;

AnimatedModel* camelloanimado;
AnimatedModel* cerdoanimado;
//AnimatedModel* ovejaanimado;
AnimatedModel* galloanimado;

float tradius = 10.0f;
float theta = 0.0f;
float alpha = 0.0f;

// Cubemap
CubeMap* mainCubeMap;

// Light gLight;
std::vector<Light> gLights;

// Materiales
Material material0;
Material material1;
Material material2;
Material material3;
Material material4;
Material material5;
Material material6;
Material material7;
Material material8;


float proceduralTime = 0.0f;
float wavesTime = 0.0f;

//Salas
int salaActual = 1;
int siguienteSala = 0;
int salaAntFrame = 1;

//Camara fija
bool fixedCam = false;
glm::vec3 lastPos(0.0f, 2.0f, 0.0f);
bool first = false;

// Audio
ISoundEngine* SoundEngine = createIrrKlangDevice();

// selección de cámara
bool    activeCamera = 1; // activamos la primera cámara
//********************************Variables globales para inicializar el juego y obtener posiciones********************************
ChessGame chessGame;
glm::vec3 posMouse(0.0f);
double xpos, ypos;
//*********************************************************************************************************************************


bool sala1Loaded = false;
bool sala2Loaded = false;
bool sala3Loaded = false;
bool sala4Loaded = false;
bool sala5Loaded = false;
bool sala6Loaded = false;

Mesh* cursorMesh = nullptr;
Shader* cursorShader = nullptr;

// Entrada a función principal
int main()
{
	if (!Start())
		return -1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		if (!Update())
			break;
	}

	// Definicion de materiales

	// MATE

	// Material 0 - "mate"
	material0.ambient = glm::vec4(0.02f, 0.02f, 0.02f, 1.0f);
	material0.diffuse = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
	material0.specular = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	material0.transparency = 1.0f;

	// Material 1 - marmol
	material1.ambient = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	material1.diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
	material1.specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
	material1.transparency = 1.0f;

	// Material 2 - madera
	material2.ambient = glm::vec4(0.4f, 0.3f, 0.2f, 1.0f);
	material2.diffuse = glm::vec4(0.6f, 0.5f, 0.4f, 1.0f);
	material2.specular = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	material2.transparency = 1.0f;

	// METALICOS

	// Material 3 - oro
	material3.ambient = glm::vec4(0.24725f, 0.1995f, 0.0745f, 1.0f);
	material3.diffuse = glm::vec4(0.75164f, 0.60648f, 0.22648f, 1.0f);
	material3.specular = glm::vec4(0.628281f, 0.555802f, 0.366065f, 1.0f);
	material3.transparency = 1.0f;

	// Material 4 - bronce
	material4.ambient = glm::vec4(0.2125f, 0.1275f, 0.054f, 1.0f);
	material4.diffuse = glm::vec4(0.714f, 0.4284f, 0.18144f, 1.0f);
	material4.specular = glm::vec4(0.393548f, 0.271906f, 0.166721f, 1.0f);
	material4.transparency = 1.0f;

	// Material 5 - cobre
	material5.ambient = glm::vec4(0.19125f, 0.0735f, 0.0225f, 1.0f);
	material5.diffuse = glm::vec4(0.7038f, 0.27048f, 0.0828f, 1.0f);
	material5.specular = glm::vec4(0.256777f, 0.137622f, 0.086014f, 1.0f);
	material5.transparency = 1.0f;

	// Material 6 - Translucido
	material6.ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	material6.diffuse = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	material6.specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
	material6.transparency = 0.8f;

	//PLASTICOS
	// Material 7 - Plastico blanco
	material7.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	material7.diffuse = glm::vec4(0.55f, 0.55f, 0.55f, 1.0f);
	material7.specular = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
	material7.transparency = 1.0;

	// Material 8 - Plastico negro
	material8.ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	material8.diffuse = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);
	material8.specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
	material8.transparency = 1.0f;

	glfwTerminate();
	return 0;

}



bool Start() {
	// Inicialización de GLFW

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creación de la ventana con GLFW
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Animation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	// Ocultar el cursor mientras se rota la escena
	glfwSetCursorPos(window, SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// glad: Cargar todos los apuntadores
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// Activación de buffer de profundidad
	glEnable(GL_DEPTH_TEST);

	// Compilación y enlace de shaders
	mLightsShader = new Shader("shaders/11_PhongShaderMultLights.vs", "shaders/11_PhongShaderMultLights.fs");
	proceduralShader = new Shader("shaders/12_ProceduralAnimation.vs", "shaders/12_ProceduralAnimation.fs");
	wavesShader = new Shader("shaders/13_wavesAnimation.vs", "shaders/13_wavesAnimation.fs");
	cubemapShader = new Shader("shaders/10_vertex_cubemap.vs", "shaders/10_fragment_cubemap.fs");
	dynamicShader = new Shader("shaders/10_vertex_skinning-IT.vs", "shaders/10_fragment_skinning-IT.fs");
	fresnelShader = new Shader("shaders/11_Fresnel.vs", "shaders/11_Fresnel.fs");
	cursorShader = new Shader("shaders/01_cursor.vs", "shaders/01_cursor.fs");

	// Máximo número de huesos: 100
	dynamicShader->setBonesIDs(MAX_RIGGING_BONES);

	// Dibujar en malla de alambre
	// glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	CambioEscena = new Model("models/General/CambioEscena.fbx");

	// Cubemap
	vector<std::string> faces
	{
		"textures/cubemap/01/posx.png",
		"textures/cubemap/01/negx.png",
		"textures/cubemap/01/posy.png",
		"textures/cubemap/01/negy.png",
		"textures/cubemap/01/posz.png",
		"textures/cubemap/01/negz.png"
	};
	mainCubeMap = new CubeMap();
	mainCubeMap->loadCubemap(faces);

	camera3rd.Position = position;
	camera3rd.Position.y += 1.7f;
	camera3rd.Position -= trdpersonOffset * forwardView;
	camera3rd.Front = forwardView;

	// Lights configuration

	Light light01;
	light01.Position = glm::vec3(0.0f, 9.0f, 0.0f);
	light01.Color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
	gLights.push_back(light01);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };


	float size = 0.01f;
	glm::vec2 square[] = {
		{-size, -size}, {size, -size}, {size, size}, {-size, size}
	};

	for (int i = 0; i < 4; ++i) {
		Vertex v = {};
		v.Position = glm::vec3(square[i], 0.0f);
		vertices.push_back(v);
	}
	cursorMesh = new Mesh(vertices, indices, {});

	return true;
}


void SetLightUniformInt(Shader* shader, const char* propertyName, size_t lightIndex, int value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setInt(uniformName.c_str(), value);
}
void SetLightUniformFloat(Shader* shader, const char* propertyName, size_t lightIndex, float value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setFloat(uniformName.c_str(), value);
}
void SetLightUniformVec4(Shader* shader, const char* propertyName, size_t lightIndex, glm::vec4 value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setVec4(uniformName.c_str(), value);
}
void SetLightUniformVec3(Shader* shader, const char* propertyName, size_t lightIndex, glm::vec3 value) {
	std::ostringstream ss;
	ss << "allLights[" << lightIndex << "]." << propertyName;
	std::string uniformName = ss.str();

	shader->setVec3(uniformName.c_str(), value);
}


bool Update() {
	// Cálculo del framerate
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Procesa la entrada del teclado o mouse
	processInput(window);

	// Renderizado R - G - B - A
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection;
	glm::mat4 view;

	if (activeCamera) {
		// Cámara en primera persona
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		view = camera.GetViewMatrix();
	}
	else {
		// cámara en tercera persona
		projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		view = camera3rd.GetViewMatrix();
	}

	// Cubemap (fondo)
	{
		mainCubeMap->drawCubeMap(*cubemapShader, projection, view);
	}

	floorOffsetZ -= floorSpeed * deltaTime;
	if (floorOffsetZ <= -10.0f) { // Ajusta -10.0f al tamaño de tu piso
		floorOffsetZ = 0.0f;
	}

	glfwGetCursorPos(window, &xpos, &ypos);
	posMouse = ScreenToWorld(xpos, ypos, projection, view, 0.2f);

	// Hace las transiciones cuando son necesarias
	cambio_escena();

	if (1 == salaActual)
	{
		if (!sala1Loaded) {
			salaInicial = new Model("models/SalaInicial/SalaInicial.obj");
			chessGame.Initialize();
			sala1Loaded = true;
		}

		if (salaActual != salaAntFrame) {
			camera.Position = glm::vec3(3.0f, 2.0f, -3.0f);
			lastPos = camera.Position;
		}
		if (chessGame.inspectMode) {
			camera.Position = chessGame.inspectCameraPosition;
			camera.Front = chessGame.inspectCameraFront;
			camera.Right = glm::normalize(glm::cross(camera.Front, camera.WorldUp));
			camera.Up = glm::normalize(glm::cross(camera.Right, camera.Front));
		}

		if (fixedCam) {
			if (first) { lastPos = camera.Position; first = false; };
			camera.Position = camera.Position = glm::vec3(-3.0f, 4.5f, 0.0f);
		}
		else {
			if (!first) { camera.Position = lastPos; first = true; }
		}
		limitBox(4.2f, -4.2f, 4.2f, -4.2f);
		// AJEDREZ
		mLightsShader->use();

		mLightsShader->setMat4("projection", projection);
		mLightsShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		mLightsShader->setMat4("model", model);

		// Configuramos propiedades de fuentes de luz
		mLightsShader->setInt("numLights", (int)gLights.size());
		for (size_t i = 0; i < gLights.size(); ++i) {
			SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
			SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
			SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
			SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
			SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
			SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
		}

		mLightsShader->setVec3("eye", camera.Position);

		// Aplicamos propiedades materiales
		mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
		mLightsShader->setVec4("MaterialDiffuseColor", material1.diffuse);
		mLightsShader->setVec4("MaterialSpecularColor", material1.specular);
		mLightsShader->setFloat("transparency", material1.transparency);

		model = glm::mat4(1.0f);

		salaInicial->Draw(*mLightsShader);
		RenderChess(mLightsShader, model);
		{
			// Obtener posición del mouse
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			int width, height;
			glfwGetWindowSize(window, &width, &height);

			float xNDC = (float(mouseX) / width) * 2.0f - 1.0f;
			float yNDC = 1.0f - (float(mouseY) / height) * 2.0f;

			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xNDC, yNDC, 0.0f));

			cursorShader->use();
			cursorShader->setMat4("projection", glm::mat4(1.0f));
			cursorShader->setMat4("view", glm::mat4(1.0f));
			cursorShader->setMat4("model", model);

			glDisable(GL_DEPTH_TEST); // Asegura que se vea por encima
			cursorMesh->Draw(*cursorShader);
			glEnable(GL_DEPTH_TEST);
		}
		salaAntFrame = 1;
	}

	else if (2 == salaActual)
	{

		if (salaActual != salaAntFrame) {
			camera.Position = glm::vec3(3.0f, 2.0f, -3.0f); //Poner aqui la posicion fija deseada
			lastPos = camera.Position;
			if (!sala2Loaded) {
				Yucatas = new Model("models/mongol/Yucatas.fbx");
				camelloanimado = new AnimatedModel("models/animales/camelloanimado.fbx");
				cerdoanimado = new AnimatedModel("models/animales/cerdoanimado.fbx");
				//ovejaanimado = new AnimatedModel("models/animales/ovejaanimado.fbx");
				galloanimado = new AnimatedModel("models/animales/galloanimado.fbx");
				sala2Loaded = true;
			}
		}

		if (fixedCam) {
			if (first) { lastPos = camera.Position; first = false; };
			camera.Position = glm::vec3(30.0f, 10.0f, -34.0f);
		}
		else {
			if (!first) { camera.Position = lastPos; first = true; }
		}

		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0, -8.0f)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			Yucatas->Draw(*mLightsShader);
			model = glm::mat4(1.0f);
		}

		{
			camelloanimado->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(1.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, camelloanimado->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			camelloanimado->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		{
			cerdoanimado->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(2.0f, 0.03f, -8.0f)); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, cerdoanimado->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			cerdoanimado->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		/* {
			 ovejaanimado->UpdateAnimation(deltaTime);

			 // Activación del shader del personaje
			 dynamicShader->use();

			 // Aplicamos transformaciones de proyección y cámara (si las hubiera)
			 dynamicShader->setMat4("projection", projection);
			 dynamicShader->setMat4("view", view);

			 // Aplicamos transformaciones del modelo
			 glm::mat4 model = glm::mat4(1.0f);
			 model = glm::translate(model, position); // translate it down so it's at the center of the scene
			 model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			 model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			 dynamicShader->setMat4("model", model);

			 dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, ovejaanimado->gBones);

			 // Dibujamos el modelo
			 glDisable(GL_CULL_FACE); // Temporal para debug
			 ovejaanimado->Draw(*dynamicShader);
			 glEnable(GL_CULL_FACE);
		 }*/

		{
			galloanimado->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-2.0f, 0.02f, -8.0f)); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, galloanimado->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			galloanimado->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}


		salaAntFrame = 2;
	}

	else if (3 == salaActual)
	{
		if (salaActual != salaAntFrame) {
			camera.Position = glm::vec3(3.0f, 2.0f, -3.0f); //Poner aqui la posicion fija deseada
			lastPos = camera.Position;
			if (!sala3Loaded) {
				character02 = new AnimatedModel("models/mongol/jinete_espada.fbx");
				character03 = new AnimatedModel("models/mongol/jinete_tug.fbx");
				character04 = new AnimatedModel("models/mongol/jinete_solo.fbx");
				caballo01 = new AnimatedModel("models/mongol/caballo1.fbx");
				character01 = new AnimatedModel("models/mongol/jinete_arquero.fbx");
				llanura_irregular = new Model("models/mongol/llanura_irregular.obj");
				monte = new Model("models/mongol/montes.fbx");
				terrenos = new Model("models/mongol/Terrenos.fbx");
				sala3Loaded = true;
			}
		}

		if (fixedCam) {
			if (first) { lastPos = camera.Position; first = false; };
			camera.Position = glm::vec3(1.5f, 5.0f, 15.0f);
		}
		else {
			if (!first) { camera.Position = lastPos; first = true; }
		}
		// *************** MODELOS ESTATICOS *********************************
		// ESCENA JINETES
			// terreno
		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, floorOffsetZ)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(200.0f, 200.0f, 200.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			terrenos->Draw(*mLightsShader);
			model = glm::mat4(1.0f);

		}

		//montes
		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, floorOffsetZ)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			monte->Draw(*mLightsShader);
			model = glm::mat4(1.0f);

		}

		//llanuras irregulares
		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(10.0f, -7.0f, floorOffsetZ)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			llanura_irregular->Draw(*mLightsShader);
			model = glm::mat4(1.0f);

		}



		// ************************* MODELOS DINAMICOS *****************************************
			// Objeto animado -- GUERRERO arco

		{
			character01->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, character01->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			character01->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}



		glUseProgram(0);

		// Objeto animado -- GUERRERO espada

		{
			character02->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, character02->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			character02->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}


		glUseProgram(0);


		// GUERRERO tug

		{
			character03->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, character03->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			character03->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}


		glUseProgram(0);

		// GUERRERO solo

		{
			character04->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, character04->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			character04->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		glUseProgram(0);

		// CABALLO

		{
			caballo01->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 position1(position.x-0.0f, position.y - 0.0f, position.z - 0.0f);
			model = glm::translate(model, position1); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, caballo01->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			caballo01->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		glUseProgram(0);

		{
			//caballo01->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 position1(position.x - 2.3f, position.y - 0.0f, position.z - 0.0f);
			model = glm::translate(model, position1); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, caballo01->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			caballo01->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		glUseProgram(0);

		{
			//caballo01->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 position1(position.x - 4.1f, position.y - 0.0f, position.z - 0.0f);
			model = glm::translate(model, position1); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, caballo01->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			caballo01->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		glUseProgram(0);


		{
			//caballo01->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			glm::vec3 position1(position.x - 6.4f, position.y - 0.0f, position.z - 0.0f);
			model = glm::translate(model, position1); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, caballo01->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			caballo01->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		glUseProgram(0);
		salaAntFrame = 3;
	}

	else if (4 == salaActual)
	{
		if (salaActual != salaAntFrame) {
			camera.Position = glm::vec3(0.0f, 3.0f, 0.0f); //Poner aqui la posicion fija deseada
			lastPos = camera.Position;
			if (!sala4Loaded) {
				templos = new Model("models/mongol/ESCENAS/AreaTemplos.fbx");
				// Puertas de templos
				puerta1 = new Model("models/mongol/ESCENAS/puerta1.fbx");
				puerta2 = new Model("models/mongol/ESCENAS/puerta2.fbx");
				sala4Loaded = true;
			}
		}
		if (fixedCam) {
			if (first) { lastPos = camera.Position; first = false;};
			camera.Position = glm::vec3(1.5f, 60.0f, 50.0f);
		}
		else {
			if(!first){ camera.Position = lastPos; first = true;}
		}
		//TEMPLO
		{
		mLightsShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mLightsShader->setMat4("projection", projection);
		mLightsShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f,0.0 , -80.0f)); // ¡Nuevo desplazamiento!
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		mLightsShader->setMat4("model", model);

		// Configuramos propiedades de fuentes de luz
		mLightsShader->setInt("numLights", (int)gLights.size());
		for (size_t i = 0; i < gLights.size(); ++i) {
			SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
			SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
			SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
			SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
			SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
			SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
		}

		mLightsShader->setVec3("eye", camera.Position);

		// Aplicamos propiedades materiales
		mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
		mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
		mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
		mLightsShader->setFloat("transparency", material0.transparency);

		templos->Draw(*mLightsShader);
		model = glm::mat4(1.0f);
		if(teleportCamera(6.3f, -5.7f, -0.9, -5.0f, glm::vec3(0.0f, 7.5f, -11.0f))) lastPos = glm::vec3(0.0f, 9.5f, -11.0f);
		else if(teleportCamera(6.3f, -5.7f, -10, -4.9f, glm::vec3(0.0f, 3.0f, 0.0f))) lastPos = glm::vec3(0.0f, 3.0f, 0.0f);
		else if(teleportCamera(-50.0f, -61.0f, -14.0f, -17.0f, glm::vec3(-55.0f, 7.5f, -23.0f))) lastPos = glm::vec3(-55.0f, 9.5f, -23.0f);
		else if(teleportCamera(-50.0f, -61.0f, -22.0f, -16.9f, glm::vec3(-55.0f, 3.0f, -12.0f))) lastPos = glm::vec3(-55.0f, 3.0f, -12.0f);
		else if(teleportCamera(50.0f, 61.0f, -14.0f, -17.0f, glm::vec3(55.0f, 7.5f, -23.0f))) lastPos = glm::vec3(55.0f, 9.5f, -23.0f);
		else if(teleportCamera(50.0f, 61.0f, -22.0f, -16.9f, glm::vec3(55.0f, 3.0f, -12.0f))) lastPos = glm::vec3(55.0f, 3.0f, -12.0f);
		}

		//PUERTAS
		{

			// Umbral de distancia para activar/desactivar (5 metros)
			const float DOOR_ACTIVATION_DISTANCE = 5.0f;

			// En tu función Update():
			glm::vec3 doorPosition = glm::vec3(0.0f, 0.0f, -23.9f); // Posición real de la puerta
			float currentDistance = glm::distance(
				glm::vec2(-camera.Position.x, -camera.Position.z),
				glm::vec2(doorPosition.x, doorPosition.z)
			);

			//std::cout << "Current distance to door: " << currentDistance << std::endl; // Debug

			if (currentDistance < DOOR_ACTIVATION_DISTANCE) {
				// Abrir progresivamente
				door_offset = glm::min(door_offset + 2.0f * deltaTime, 5.0f);
				//std::cout << "Opening door... Current offset: " << door_offset << std::endl;
			}
			else if (currentDistance > DOOR_ACTIVATION_DISTANCE + 1.0f) { // Pequeño hysteresis
				// Cerrar progresivamente
				door_offset = glm::max(door_offset - 2.0f * deltaTime, 0.0f);
				//std::cout << "Closing door... Current offset: " << door_offset << std::endl;
			}



			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(door_offset, 0.0, -79.9f)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			puerta1->Draw(*mLightsShader);
			model = glm::mat4(1.0f);
		}

		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0, 0.0, -80.0f)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			puerta2->Draw(*mLightsShader);
			model = glm::mat4(1.0f);
		}


		salaAntFrame = 4;
	}

	else if (5 == salaActual)
	{

		if (salaActual != salaAntFrame) {
			camera.Position = glm::vec3(3.0f, 2.0f, -3.0f); //Poner aqui la posicion fija deseada
			if (!sala5Loaded) {
				AldeaVikinga = new Model("models/vikingos/PuebloVik.fbx");
				aguapueblo = new Model("models/vikingos/aguapueblo.fbx");
				cerdoanimado = new AnimatedModel("models/animales/cerdoanimado.fbx");
				galloanimado = new AnimatedModel("models/animales/galloanimado.fbx");
				sala5Loaded = true;
			}
		}
		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0, -8.0f)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			AldeaVikinga->Draw(*mLightsShader);
			model = glm::mat4(1.0f);
		}

		{
			// Activamos el shader de Phong
			fresnelShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			fresnelShader->setMat4("projection", projection);
			fresnelShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -7.5f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			fresnelShader->setMat4("model", model);
			fresnelShader->setVec3("cameraPosition", camera.Position);
			fresnelShader->setFloat("mRefractionRatio", 1.0f / 1.333f); // 1.333 Agua
			fresnelShader->setFloat("_Bias", 0.2f);
			fresnelShader->setFloat("_Scale", 0.5f);
			fresnelShader->setFloat("_Power", 0.5f);
			aguapueblo->Draw(*fresnelShader);

		}

		{
			galloanimado->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-2.0f, 0.02f, -8.0f)); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, galloanimado->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			galloanimado->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}

		{
			cerdoanimado->UpdateAnimation(deltaTime);

			// Activación del shader del personaje
			dynamicShader->use();

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			dynamicShader->setMat4("projection", projection);
			dynamicShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(34.0f, 0.00f, -43.0f)); // translate it down so it's at the center of the scene
			model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.008f, 0.008f, 0.008f));	// it's a bit too big for our scene, so scale it down

			dynamicShader->setMat4("model", model);

			dynamicShader->setMat4("gBones", MAX_RIGGING_BONES, cerdoanimado->gBones);

			// Dibujamos el modelo
			glDisable(GL_CULL_FACE); // Temporal para debug
			cerdoanimado->Draw(*dynamicShader);
			glEnable(GL_CULL_FACE);
		}


		glUseProgram(0);
		salaAntFrame = 5;
	}

	else if (6 == salaActual)
	{

		if (salaActual != salaAntFrame) {
			camera.Position = glm::vec3(3.0f, 2.0f, -3.0f); //Poner aqui la posicion fija deseada
			if (!sala6Loaded) {
				EmbarcacionVik = new Model("models/vikingos/embarcacion.fbx");
				aguaembarcacion = new Model("models/vikingos/agua_embarcacion.fbx");
				sala6Loaded = true;
			}
		}

		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0, -8.0f)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			EmbarcacionVik->Draw(*mLightsShader);
			model = glm::mat4(1.0f);
		}

		{
			// Activamos el shader de Phong
			wavesShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Aplicamos transformaciones de proyección y cámara (si las hubiera)
			wavesShader->setMat4("projection", projection);
			wavesShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
			wavesShader->setMat4("model", model);
			wavesShader->setVec3("cameraPosition", camera.Position);
			wavesShader->setFloat("mRefractionRatio", 1.0f / 1.333f); // 1.333 Agua
			wavesShader->setFloat("_Bias", 0.2f);
			wavesShader->setFloat("_Scale", 0.5f);
			wavesShader->setFloat("_Power", 0.5f);
			wavesShader->setFloat("time", wavesTime);
			wavesShader->setFloat("radius", 1.0f);
			wavesShader->setFloat("height", 1.0f);

			aguaembarcacion->Draw(*wavesShader);
			wavesTime += 0.01;

		}

		glUseProgram(0);
		salaAntFrame = 6;
	}

	// Transicion de escena
	{
		{
			mLightsShader->use();

			// Activamos para objetos transparentes
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			mLightsShader->setMat4("projection", projection);
			mLightsShader->setMat4("view", view);

			// Aplicamos transformaciones del modelo
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(camera.Position.x, alturaTransEs, camera.Position.z)); // ¡Nuevo desplazamiento!
			model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
			mLightsShader->setMat4("model", model);

			// Configuramos propiedades de fuentes de luz
			mLightsShader->setInt("numLights", (int)gLights.size());
			for (size_t i = 0; i < gLights.size(); ++i) {
				SetLightUniformVec3(mLightsShader, "Position", i, gLights[i].Position);
				SetLightUniformVec3(mLightsShader, "Direction", i, gLights[i].Direction);
				SetLightUniformVec4(mLightsShader, "Color", i, gLights[i].Color);
				SetLightUniformVec4(mLightsShader, "Power", i, gLights[i].Power);
				SetLightUniformInt(mLightsShader, "alphaIndex", i, gLights[i].alphaIndex);
				SetLightUniformFloat(mLightsShader, "distance", i, gLights[i].distance);
			}

			mLightsShader->setVec3("eye", camera.Position);

			// Aplicamos propiedades materiales
			mLightsShader->setVec4("MaterialAmbientColor", material0.ambient);
			mLightsShader->setVec4("MaterialDiffuseColor", material0.diffuse);
			mLightsShader->setVec4("MaterialSpecularColor", material0.specular);
			mLightsShader->setFloat("transparency", material0.transparency);

			CambioEscena->Draw(*mLightsShader);
			model = glm::mat4(1.0f);
		}
	}


	// glfw: swap buffers 
	glfwSwapBuffers(window);
	glfwPollEvents();

	return true;
}

// Procesamos entradas del teclado
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);


	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		cambiandoEscena = true;
		siguienteSala = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		cambiandoEscena = true;
		siguienteSala = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		cambiandoEscena = true;
		siguienteSala = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		cambiandoEscena = true;
		siguienteSala = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		cambiandoEscena = true;
		siguienteSala = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		cambiandoEscena = true;
		siguienteSala = 6;
	}


	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		door_offset += 0.01f;
		// Limitar máximo 
		if (door_offset > 3.5f) {
			door_offset = 3.5f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		door_offset -= 0.01f;
		// Limitar mínimo a 0
		if (door_offset < 0.0f) {
			door_offset = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		door_rotation += 1.f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		door_rotation -= 1.f;

	// Character movement
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

		position = position + scaleV * forwardView;
		camera3rd.Front = forwardView;
		camera3rd.ProcessKeyboard(FORWARD, deltaTime);
		camera3rd.Position = position;
		camera3rd.Position.y += 1.7f;
		camera3rd.Position -= trdpersonOffset * forwardView;

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position = position - scaleV * forwardView;
		camera3rd.Front = forwardView;
		camera3rd.ProcessKeyboard(BACKWARD, deltaTime);
		camera3rd.Position = position;
		camera3rd.Position.y += 1.7f;
		camera3rd.Position -= trdpersonOffset * forwardView;
	}

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		activeCamera = 0;
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		activeCamera = 1;

	if (chessGame.inspectMode) {
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			chessGame.inspectRotation -= 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			chessGame.inspectRotation += 1.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		fixedCam = true;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		fixedCam = false;
}

void cambio_escena()
{
	if (cambiandoEscena)
	{
		if (alturaTransEs < 0.3)
		{
			alturaTransEs += 0.003f;
		}
		else
		{
			salaActual = siguienteSala;
			cambiandoEscena = false;
		}
	}
	else
	{
		if (alturaTransEs > -3.0f)
		{
			alturaTransEs -= 0.003f;
		}
	}
}


// glfw: Actualizamos el puerto de vista si hay cambios del tamaño
// de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// glfw: Callback del movimiento y eventos del mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (chessGame.inspectMode && salaActual == 1)return;
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: Complemento para el movimiento y eventos del mouse
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}
//*****************************************Definición de la función para renderizar piezas*****************************************
void RenderChess(Shader* shader, glm::mat4 model) {
	model = glm::mat4(1.0f);
	shader->setMat4("model", model);
	chessGame.Tablero->Draw(*shader);

	for (Character& current : chessGame.whites) {
		if (current.alive) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, *current.position);
			// Aplicar rotación si está en modo inspección y es la pieza seleccionada
			if (chessGame.inspectMode && chessGame.selected == &current) {
				model = glm::rotate(model, glm::radians(chessGame.inspectRotation), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			shader->setMat4("model", model);
			current.model->Draw(*shader);
		}
	}

	for (Character& current : chessGame.blacks) {
		if (current.alive) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, *current.position);
			// Aplicar rotación si está en modo inspección y es la pieza seleccionada
			if (chessGame.inspectMode && chessGame.selected == &current) {
				model = glm::rotate(model, glm::radians(chessGame.inspectRotation), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			shader->setMat4("model", model);
			current.model->Draw(*shader);
		}
	}
}
//*****************************************************************************************************************************


//*****************************************************************************************************************************
//Función para convertir coordenadas del mouse a coordenadas del mundo relacionadas a las casillas del tablero (plano Y=0.2)
glm::vec3 ScreenToWorld(double xpos, double ypos, glm::mat4 projection, glm::mat4 view, float planeY = 0.2f) {
	// Convertir coordenadas del mouse a NDC
	double x = (2.0f * xpos) / SCR_WIDTH - 1.0f;
	double y = 1.0f - (2.0f * ypos) / SCR_HEIGHT;

	// Crear vector en espacio de clip
	glm::vec4 rayClip = glm::vec4(x, y, -1.0f, 1.0f);

	// Convertir a espacio de ojos (eye space)
	glm::mat4 invProjection = glm::inverse(projection);
	glm::vec4 rayEye = invProjection * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

	// Convertir a espacio del mundo
	glm::mat4 invView = glm::inverse(view);
	glm::vec4 rayWorld = invView * rayEye;
	glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld));

	// Calcular intersección con el plano Y = planeY
	float t = (planeY - camera.Position[1]) / rayDir.y;
	glm::vec3 worldPos = camera.Position + t * rayDir;

	float cellSize = 0.6f; // Distancia entre casillas
	float boardOriginX = -2.1f; // Origen del tablero en X
	float boardOriginZ = -2.1f; // Origen del tablero en Z
	int boardSize = 8;          // Tamaño 8x8 casillas

	// Calcular casilla
	float relativeX = (worldPos.x - boardOriginX) / cellSize;
	float relativeZ = (worldPos.z - boardOriginZ) / cellSize;

	int cellX = static_cast<int>(round(relativeX));
	int cellZ = static_cast<int>(round(relativeZ));

	//// Verificar si está dentro del tablero
	//if (cellX < 0 || cellX >= boardSize || cellZ < 0 || cellZ >= boardSize) {
	//	// Fuera del tablero
	//	return glm::vec3(9999.0f);
	//}

	// Calcular posición centrada
	float snappedX = boardOriginX + cellX * cellSize;
	float snappedZ = boardOriginZ + cellZ * cellSize;

	return glm::vec3(snappedX, planeY, snappedZ);
}
//*****************************************************************************************************************************

//****************************************Funcion para manejar agarrar y soltar piezas****************************************
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << "(" << posMouse.x << "," << posMouse.y << "," << posMouse.z << ")" << std::endl;
		chessGame.HandleMouseClick(posMouse);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		chessGame.HandleRightClick();
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		chessGame.HandleMiddleClick(posMouse, camera);
	}
}

//*****************************************************************************************************************************

//****************************************Funcion para limitar camara en una caja****************************************
void limitBox(float xMax, float xMin, float zMax, float zMin) {
	if (camera.Position[0] > xMax) camera.Position[0] = xMax;
	if (camera.Position[0] < xMin) camera.Position[0] = xMin;
	if (camera.Position[2] > zMax) camera.Position[2] = zMax;
	if (camera.Position[2] < zMin) camera.Position[2] = zMin;
}
//***********************************************************************************************************************

//****************************************Funcion para transportar la camara segun su posicion****************************************
bool teleportCamera(float xMax, float xMin, float zMax, float zMin, glm::vec3 newPos) {
	if (xMin > xMax) std::swap(xMin, xMax);
	if (zMin > zMax) std::swap(zMin, zMax);
	if (reachBox(xMax, xMin, zMax, zMin)) { camera.Position = newPos; return true;}
	return false;
}
//************************************************************************************************************************************

//****************************************Funcion para detectar si la camara ha llegado a una zona cuadrada definida****************************************
bool reachBox(float xMax, float xMin, float zMax, float zMin) {
	if (camera.Position[0] <= xMax && camera.Position[0] >= xMin) {
		if (camera.Position[2] <= zMax && camera.Position[2] >= zMin) return true;
	}
	return false;
}
//***********************************************************************************************************************************************************

//SENSOR PARA LA PEURTA
bool isPlayerNearDoor(const glm::vec3& playerPosition, const glm::vec3& doorPosition, float threshold) {
	// Ignora la coordenada Y para comparación solo en plano XZ
	glm::vec2 playerXZ(playerPosition.x, playerPosition.z);
	glm::vec2 doorXZ(doorPosition.x, doorPosition.z);
	float distance = glm::distance(playerXZ, doorXZ);

	std::cout << "Calculated 2D distance: " << distance << std::endl; // Debug

	return distance < threshold;
}