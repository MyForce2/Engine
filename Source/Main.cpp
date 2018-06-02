#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include "Utils\Clock.h"
#include "Utils\Log.h"


#include <iostream>
#include <chrono>
#include <thread>

#define BLOCKS true


using namespace Engine;
using namespace Math;
using namespace Graphics;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

static const int WIDTH = 1600;
static const int HEIGHT = 900;
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

void fillColorBuffer(float* buffer) {
	srand(time(NULL));
	for (int i = 0; i < 36 * 3; i++) {
		float val = float(rand() % 256);
		val /= 256;
		buffer[i] = val;
	}
}


void test(Mat4& model, float time, float tUnit) {
	Vec3 trans = Vec3(tUnit, tUnit, 0.f);
	float angle = time * ANGLE_PER_SEC;
	model = Mat4::translation(trans * -1) * model;
	model = Mat4::rotationZ(angle) * model;
	model = Mat4::translation(trans) * model;
}

void handleInput(const Window& window, Camera* camera, float time) {
	float cameraSpeed = 6.f * time;
	Vec3 pos = camera->getPosition();
	Vec3 direction = camera->getViewingDirection();
	if (window.isKeyPressed(GLFW_KEY_T)) {
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
	Utils::Log::getLog()->logMessage("Starting engine");
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		Utils::Log::getLog()->logError("Failed to init glew, terminating");
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Vec3 red(1.f, 0.f, 0.f);
	Vec3 clearColor(0.f / 256.f, 191.f / 256.f, 255.f / 256.f);
	glClearColor(red.x, red.y, red.z, 1.f);
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positionsTex[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		// Right face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
	};

	float positions[] = {
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5,
		0.5f, -0.5f, 0.5,
		-0.5f, -0.5f, 0.5,
		-0.5f, 0.5f, 0.5
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 3, 2,
		0, 1, 5,
		0, 4, 5,
		0, 3, 4,
		4, 7, 3,
		4, 5, 6,
		4, 7, 6,
		7, 3, 2,
		7, 6, 2,
		1, 2, 5,
		6, 5, 2
	};

	float colorBuffer[36 * 3];
	srand(time(nullptr));
	for (int i = 0; i < 36 * 3; i++) {
		float val = float(rand() % 256);
		val /= 256;
		colorBuffer[i] = val;
	}

	int lim = 30;
	int distance = 3;
	int amount;
	if (lim % distance == 0) {
		amount = lim / distance;
	} else {
		amount = lim / distance + lim % distance;
	}

	int objAmount = amount * amount * amount;

	Mat4* translationsBuffer = new Mat4[objAmount];
	int index = 0;
	for (int x = 0; x < lim; x += distance) {
		for (int y = 0; y < lim; y += distance) {
			for (int z = 0; z < lim; z += distance) {
				Vec3 translation(x, y, z);
				Mat4 rotation = Mat4::rotationX(90.f);
				translationsBuffer[index] = Mat4::translation(translation) * rotation;
				index++;
			}
		}
	}





	VertexArray vao;
	VBLayout colorLayout;
	VBLayout verticesLayout;
	colorLayout.addElement(3, GL_FLOAT);
	verticesLayout.addElement(3, GL_FLOAT);
	verticesLayout.addElement(2, GL_FLOAT);
	VertexBuffer colors(colorBuffer, sizeof(colorBuffer));
	VertexBuffer posTex(positionsTex, sizeof(positionsTex));
	VertexBuffer translations(translationsBuffer, objAmount * sizeof(Mat4));
	vao.addBuffer(posTex, verticesLayout);
	vao.addBuffer(colors, colorLayout);
	vao.addMatrixBuffer(translations);
	vao.bind();
	Shader shader("Resources/Shaders/Vertex.shader", "Resources/Shaders/Fragment.shader");
	Mat4 matrix(1.f);
	float w = float(WIDTH);
	float h = float(HEIGHT);
	Camera c(window, 0.1f, 100.f);
	c.setPosition(Vec3(40, 0, 15));
	c.setViewingDirection(Vec3(0, 0, -1.f));
	c.update(window);
	Mat4 model(1.f);
	Texture t("Resources/Textures/Texture.png");
	t.setSlot();
	shader.setUniformMatrix4fv("view", c.getViewMatrix());
	shader.setUniformMatrix4fv("model", model);
	shader.setUniformMatrix4fv("projection", c.getProjectionMatrix());
	shader.setUniform1i("texSlot", 0);
	shader.setUniform3f("lightColor", clearColor);
	Vec3 pointA(5, 6, 0);
	Vec3 pointB(10, 12, 0);
	std::cout << pointA.distance(pointB) << std::endl;

	vao.bind();
	shader.bind();
	window.setMousePosition(window.getSize() / 2);

	delete[] translationsBuffer;

	Utils::Clock clock;

	
	int max = lim * lim * lim;

	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		handleInput(window, &c, clock.getTimePassed());
		clock.reset();
		c.update(window);
		shader.setUniformMatrix4fv("view", c.getViewMatrix());
#if BLOCKS
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, max);
#else
		glDrawArrays(GL_TRIANGLES, 0, 36);
#endif
		window.update();
	}
	glfwTerminate();
	Utils::Log::closeLog();
	return EXIT_SUCCESS;
}