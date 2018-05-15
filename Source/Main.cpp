#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace Engine;
using namespace Math;
using namespace Graphics;

static const int WIDTH = 1280;
static const int HEIGHT = 720;



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


void test(Mat4& model, float angle, float tUnit) {
	model = Mat4::translation(Vec3(-tUnit, -tUnit, 0.f)) * model;
	model = Mat4::rotationZ(angle) * model;
	model = Mat4::translation(Vec3(tUnit, tUnit, 0.f)) * model;
}




int main() {
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	float positions[] = {
		600.f, 600.f,
		600.f, 500.f,
		500.f, 500.f,
		500.f, 600.f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	
	
	VertexBuffer vbo(positions, sizeof(positions) * sizeof(float));
	IndexBuffer ibo(indices, 6);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*) 0);
	Shader shader("Resources/Shaders/Vertex.shader", "Resources/Shaders/Fragment.shader");
	shader.bind();
	float w = (float) WIDTH;
	float h = (float) HEIGHT;
	Mat4 projection = Mat4::orthographic(0.f, w, 0.f, h, -1.f, 1.f);
	Mat4 model(1.f);
	Mat4 view(1.f);
	Mat4 modelTwo(1.f);
	test(model, 45.f, 550.f);
	test(modelTwo, 45.f, 550.f);
	modelTwo = Mat4::translation(Vec3(100.f, -100.f, 0.f)) * modelTwo;
	shader.setUniformMatrix4fv("u_View", view);
	shader.setUniformMatrix4fv("u_Projection", projection);
	shader.setUniformMatrix4fv("u_Model", model);

	auto start = std::chrono::high_resolution_clock::now();
	float perSec = 180.f;
	while (!window.isClosed() && !window.isKeyPressed(GLFW_KEY_ESCAPE)) {
		shader.setUniformMatrix4fv("u_Model", model);
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		shader.setUniformMatrix4fv("u_Model", modelTwo);
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> d = end - start;
		float angle = perSec * d.count();
		test(model, angle, 550.f);
		start = end;
		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}