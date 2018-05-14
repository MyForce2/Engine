#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Window.h"

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


	while (!window.isClosed() && !window.isKeyPressed(GLFW_KEY_ESCAPE)) {

		float p = 0.25;
		glBegin(GL_QUADS);
		glVertex2f(p, p);
		glVertex2f(p, -p);
		glVertex2f(-p, -p);
		glVertex2f(-p, p);
		glEnd();
		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}