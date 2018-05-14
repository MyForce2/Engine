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
		std::cout << duration.count() << " ms" << std::endl;
	}
};





int main() {
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	float positions[] = {
		0.25, 0.25,
		0.25, -0.25,
		-0.25, -0.25,
		-0.25, 0.25
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
	

	while (!window.isClosed() && !window.isKeyPressed(GLFW_KEY_ESCAPE)) {

		float p = 0.25;
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}