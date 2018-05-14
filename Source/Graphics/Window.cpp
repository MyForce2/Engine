#pragma once

#include <GLFW\glfw3.h>
#include <iostream>

#include "Window.h"

namespace Engine {
	namespace Graphics {

		Window::Window(const std::string& title, int height, int width) : title(title), height(height), width(width) {
			if (!glfwInit())
				std::cout << "Failed to init" << std::endl;
			glfwWindowHint(GLFW_SAMPLES, 4);
			windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (!windowHandle) {
				std::cout << "Failed to create window" << std::endl;
			}
			glfwMakeContextCurrent(windowHandle);
			glfwSwapInterval(0);
			updateMousePosition();
		}

		Window::~Window() {
			glfwDestroyWindow(windowHandle);
		}

		bool Window::isClosed() const {
			return glfwWindowShouldClose(windowHandle);
		}

		bool Window::isKeyPressed(int key) const {
			return glfwGetKey(windowHandle, key) == GLFW_PRESS;
		}

		bool Window::isKeyReleased(int key) const {
			return glfwGetKey(windowHandle, key) == GLFW_RELEASE;
		}

		void Window::update() {
			glfwSwapBuffers(windowHandle);
			glfwPollEvents();
			updateMousePosition();
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void Window::updateMousePosition() {
			double x, y;
			glfwGetCursorPos(windowHandle, &x, &y);
			mousePosition.x = (float) x;
			mousePosition.y = (float) y;
		}
	}
}