#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include "Utils\Clock.h"
#include "Graphics\Camera2D.h"
#include "Graphics\Camera.h"


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
static const float ANGLE_PER_MSEC = 60.f;

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




void test(Mat4& model, float time, float tUnit) {
	Vec3 trans = Vec3(tUnit, tUnit, 0.f);
	float angle = time * ANGLE_PER_MSEC;
	model = Mat4::translation(trans * -1) * model;
	model = Mat4::rotationZ(angle) * model;
	model = Mat4::translation(trans) * model;
}

float* generateColorBuffer() {
	float* buffer = new float[COLOR_BUFFER_SIZE]();
	srand(time(NULL));
	for (int i = 0; i < COLOR_BUFFER_SIZE; i += 4) {
		buffer[i] = (float) (rand() % 256);
		buffer[i + 1] = (float) (rand() % 256);
		buffer[i + 2] = (float) (rand() % 256);
		buffer[i + 3] = 1.f;
	}
	return buffer;
}



int main() {
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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
		3, 7, 4,
		1, 2, 5,
		5, 6, 2,
		3, 2, 6,
		3, 7, 6,
	};

	float colorBuffer[8 * 3];
	srand(time(nullptr));
	for (int i = 0; i < 8 * 3; i++) {
		float val = rand() % 256;
		val /= 256;
		colorBuffer[i] = val;
	}

	VertexArray vao;
	VBLayout layout;
	layout.addElement(3, GL_FLOAT);
	VertexBuffer vbo(positions, sizeof(positions));
	VertexBuffer colors(colorBuffer, sizeof(float) * COLOR_BUFFER_SIZE);
	vao.addBuffer(vbo, layout);
	vao.addBuffer(colors, layout);
	vao.bind();
	IndexBuffer ibo(indices, sizeof(indices) / sizeof(unsigned int));
	Shader shader("Resources/Shaders/Vertex.shader", "Resources/Shaders/Fragment.shader");
	Mat4 matrix(1.f);
	float w = (float) WIDTH;
	float h = (float) HEIGHT;
	Camera c;
	c.setPosition(Vec3(4, 2, 3));
	c.setViewingDirection(Vec3(0, 0, 0));
	Mat4 view = c.generateViewMatrix();
	Mat4 model = Mat4::scale(Vec3(3.f));
	Mat4 projection = Mat4::perspective(w / h, 90.f, -1.f, 1.f);
	shader.setUniformMatrix4fv("view", view);
	shader.setUniformMatrix4fv("model", model);
	shader.setUniformMatrix4fv("projection", projection);

	


	ibo.bind();
	vao.bind();
	shader.bind();

	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}