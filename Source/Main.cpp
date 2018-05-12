#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"

#include <iostream>

using namespace Engine;
using namespace Math;

static const int WIDTH = 1280;
static const int HEIGHT = 720;

template<typename T>
inline void print(T type) {
	std::cout << type << std::endl;
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