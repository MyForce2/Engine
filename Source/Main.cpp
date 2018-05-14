#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace Engine;
using namespace Math;

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


void testOne() {
	Timer t;
	Vec3 a(1.f, 0.f, 0.f);
	for (int i = 0; i < 1000000; i++) {
		Mat4 m = Mat4::rotation(45.f, a);
	}
	std::cout << "ONE ----------" << std::endl;
}

void testTwo() {
	Timer t;
	for (int i = 0; i < 1000000; i++) {
		Mat4 m = Mat4::rotateX(45.f);
	}
	std::cout << "TWO ----------" << std::endl;
}


int main() {
	GLFWwindow* window;
	if (!glfwInit())
		return EXIT_FAILURE;

	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Engine", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::thread a(testOne);
	std::thread b(testTwo);
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {

		glClear(GL_COLOR_BUFFER_BIT);

		float p = 0.25;
		glBegin(GL_QUADS);
		glVertex2f(p, p);
		glVertex2f(p, -p);
		glVertex2f(-p, -p);
		glVertex2f(-p, p);
		glEnd();
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}