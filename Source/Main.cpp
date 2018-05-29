#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include "Utils\Clock.h"
#include "Utils\Log.h"


#include <iostream>
#include <chrono>
#include <thread>


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
	camera->setPosition(pos);
}

int main() {
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		Utils::logError("Failed to init glew, terminating");
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	Vec3 clearColor(0.f / 256.f, 191.f / 256.f, 255.f / 256.f);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.f);
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positionsTex[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

	VertexArray vao;
	VBLayout colorLayout;
	VBLayout verticesLayout;
	colorLayout.addElement(3, GL_FLOAT);
	verticesLayout.addElement(3, GL_FLOAT);
	verticesLayout.addElement(2, GL_FLOAT);
	VertexBuffer colors(colorBuffer, sizeof(colorBuffer));
	VertexBuffer posTex(positionsTex, sizeof(positionsTex));
	vao.addBuffer(posTex, verticesLayout);
	vao.addBuffer(colors, colorLayout);
	vao.bind();
	Shader shader("Resources/Shaders/Vertex.shader", "Resources/Shaders/Fragment.shader");
	Mat4 matrix(1.f);
	float w = float(WIDTH);
	float h = float(HEIGHT);
	Camera c;
	c.setPosition(Vec3(30, 0, 30));
	c.setViewingDirection(Vec3(0, 0, -1.f));
	Mat4 view = c.generateViewMatrix();
	Mat4 model(1.f);
	float near = 0.1f;
	float far = 100.f;
	float fov = 45.f;
	Mat4 projection = Mat4::perspective(w / h, fov, 0.1f, 100.f);
	Texture t("Resources/Textures/Texture.png");
	t.setSlot();
	shader.setUniformMatrix4fv("view", view);
	shader.setUniformMatrix4fv("model", model);
	shader.setUniformMatrix4fv("projection", projection);
	shader.setUniform1i("texSlot", 0);

	vao.bind();
	shader.bind();
	window.setMousePosition(window.getSize() / 2);

	int lim = 5;

	Utils::Clock clock;
	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		handleInput(window, &c, clock.getTimePassed());
		clock.reset();
		c.updateViewDirection(window);
		shader.setUniformMatrix4fv("view", c.generateViewMatrix());
		for (int x = 0; x < lim; x++) {
			for (int y = 0; y < lim; y++) {
				for (int z = 0; z < lim; z++) {
					shader.setUniformMatrix4fv("model", Mat4::translation(Vec3(float(x), float(y), float(z))));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}
		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}