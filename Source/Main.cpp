#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include <Typo/Typo.h>
#include <vector>
#include "Utils/Utils.h"
#include <Windows.h>
#include "Graphics/Layers/Layer2D.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>

#define BLOCKS true

using namespace Engine;
using namespace Math;
using namespace Graphics;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

static const int WIDTH = 1280;
static const int HEIGHT = 720;
static const float ANGLE_PER_SEC = 120.f;

static const int COLOR_BUFFER_SIZE = 8 * 3;



struct Timer {

	std::chrono::time_point<std::chrono::steady_clock> start;

	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		std::cout << duration.count() * 1000 << " ms" << std::endl;
	}
};

Vec3* createNormalsBuffer(float* vertices) {
	return nullptr;
}


void handleInput(const Window& window, Camera* camera, float time) {
	float cameraSpeed = 6.f * time;
	Vec3 pos = camera->getPosition();
	Vec3 direction = camera->getViewingDirection();
	if (window.isKeyPressed(GLFW_KEY_X)) {
		cameraSpeed *= 10;
	}
	if (window.isKeyPressed(GLFW_KEY_S)) {
		pos -= direction * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_W)) {
		pos += direction * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_A)) {
		pos -= direction.cross(Vec3(0, 1, 0)).normalized() * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_D)) {
		pos += direction.cross(Vec3(0, 1, 0)).normalized() * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_SPACE)) {
		pos += Vec3(0, 1, 0) * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_R)) {
		pos -= Vec3(0, 1, 0) * cameraSpeed;
	}
	camera->setPosition(pos);
}

int main() {
	Utils::Log::getLog()->logInfo("Starting run");
	Window window("Engine", HEIGHT, WIDTH, GL_COLOR_BUFFER_BIT);
	if (glewInit() != GLEW_OK) {
		Utils::Log::getLog()->logError("Failed to init glew, terminating");
		return EXIT_FAILURE;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*Vec3 clearColor(0.f / 255.f, 191.f / 255.f, 255.f / 255.f);*/
	Vec3 clearColor(0.f / 255.f, 0.f / 255.f, 0.f / 255.f);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.f);
	std::cout << glGetString(GL_VERSION) << std::endl;


	//float positionsTex[] = {
	//	-1.f, -1.f, -1.f,  xMinA, yMinA, // Bottom-left
	//	1.f,  1.f, -1.f,  xMaxA, yMaxA, // top-right
	//	1.f, -1.f, -1.f,  xMaxA, yMinA, // bottom-right         
	//	1.f,  1.f, -1.f,  xMaxA, yMaxA, // top-right
	//	-1.f, -1.f, -1.f,  xMinA, yMinA, // bottom-left
	//	-1.f,  1.f, -1.f,  xMinA, yMaxA, // top-left
	//	
	//	// Front face
	//	-1.f, -1.f,  1.f,   xMinA, yMinA, // bottom-left
	//	1.f, -1.f,  1.f,   xMaxA, yMinA,  // bottom-right
	//	1.f,  1.f,  1.f,   xMaxA, yMaxA,  // top-right
	//	1.f,  1.f,  1.f,   xMaxA, yMaxA,  // top-right
	//	-1.f,  1.f,  1.f,   xMinA, yMaxA, // top-left
	//	-1.f, -1.f,  1.f,   xMinA, yMinA, // bottom-left
	//	// Left face
	//	-1.f,  1.f,  1.f,  xMax, yMax, // top-right
	//	-1.f,  1.f, -1.f,  xMin, yMax, // top-left
	//	-1.f, -1.f, -1.f,  xMin, yMin, // bottom-left
	//	-1.f, -1.f, -1.f,  xMin, yMin, // bottom-left
	//	-1.f, -1.f,  1.f,  xMax, yMin, // bottom-right
	//	-1.f,  1.f,  1.f,  xMax, yMax, // top-right
	//	// Right face
	//	1.f,  1.f,  1.f,  xMin, yMax, // top-left
	//	1.f, -1.f, -1.f,  xMax, yMin, // bottom-right
	//	1.f,  1.f, -1.f,  xMax, yMax, // top-right         
	//	1.f, -1.f, -1.f,  xMax, yMin, // bottom-right
	//	1.f,  1.f,  1.f,  xMin, yMax, // top-left
	//	1.f, -1.f,  1.f,  xMin, yMin, // bottom-left     
	//	// Bottom face
	//	-1.f, -1.f, -1.f,  xMax, yMax, // top-right
	//	1.f, -1.f, -1.f,  xMin, yMax, // top-left
	//	1.f, -1.f,  1.f,  xMin, yMin, // bottom-left
	//	1.f, -1.f,  1.f,  xMin, yMin, // bottom-left
	//	-1.f, -1.f,  1.f,  xMax, yMin, // bottom-right
	//	-1.f, -1.f, -1.f,  xMax, yMax, // top-right
	//	// Top face
	//	-1.f,  1.f, -1.f,  xMin, yMax, // top-left
	//	1.f,  1.f,  1.f,  xMax, yMin, // bottom-right
	//	1.f,  1.f, -1.f,  xMax, yMax, // top-right     
	//	1.f,  1.f,  1.f,  xMax, yMin, // bottom-right
	//	-1.f,  1.f, -1.f,  xMin, yMax, // top-left
	//	-1.f,  1.f,  1.f,  xMin, yMin  // bottom-left
	//};

	



	//glClearColor(0.32f, 0.53f, 0.53f, 0.f);


	







	//TyMax = 1.f;
	//TyMin = 0.f;
	//TxMax = 1.f;
	//TxMin = 0.f;

	float xMin = 60.f;
	float xMax = 80.f;
	float yMin = 60.f;
	float yMax = 80.f;
	



	/*Texture texture("Resources/Textures/grass_side.png");
	texture.setSlot();*/

	GLfloat data[] = {
		xMax, yMax, 1.f, 1.f,
		xMin, yMax, 0.f, 1.f,
		xMin, yMin, 0.f, 0.f,
		xMax, yMin, 1.f, 0.f
	};

	const GLushort indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat dataTwo[8];
	for (int i = 0; i < 8; i++)
		dataTwo[i] = data[i] * 3;





	BasicRenderer renderer;
	std::string path = "Resources/Shaders/";
	Layer2D layer = Layer2D(512.f, 512.f, path + "QuadVertex.shader", path + "QuadFragment.shader");

	Renderable2DTexture obj = Renderable2DTexture(data, sizeof(data), "Resources/Textures/grass_side.png");
	Renderable2DTexture objTwo = Renderable2DTexture(data, sizeof(data), "Resources/Textures/grass_side.png");


	Label one = Label("One", 36, Vec2(100, 300), Vec3(100, 100, 0));
	Label two = Label("Two", 36, Vec2(100, 100), Vec3(0, 100, 100));
	Vec2 t(100, 0);
	Mat4 m = Mat4::translation(t);
	one.setModelMatrix(m);



	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		layer.startFrame();
		layer.add(one);
		layer.add(two);
		layer.render();
		window.update();
	}

	glfwTerminate();
	Utils::Log::closeLog();
	return EXIT_SUCCESS;
}