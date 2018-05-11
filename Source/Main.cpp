#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>


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

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, 0.f);
		glVertex2f(0.f, 1.f);
		glVertex2f(0.5f, 0.f);
		glVertex2f(-0.5f, 0.f);
		glVertex2f(0.f, 1.f);
		glVertex2f(0.5f, 0.f);
		glEnd();
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}