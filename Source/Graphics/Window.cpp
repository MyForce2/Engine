#pragma once

#include <GLFW\glfw3.h>
#include <iostream>

#include "Window.h"
#include "Utils\Log.h"

namespace Engine {
	namespace Graphics {

		Window::Window(const std::string& title, int height, int width) : title(title), height(height), width(width) {
			if (!glfwInit())
				Utils::logError("Failed to init glfw");
			glfwWindowHint(GLFW_SAMPLES, 4);
			windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (!windowHandle) {
				Utils::logError("Failed to create window");
			}
			glfwMakeContextCurrent(windowHandle);
			glfwSwapInterval(0);
			glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			setMousePosition(getSize() / 2);
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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		Math::Vec2 Window::getMousePosition() const {
			double x, y;
			glfwGetCursorPos(windowHandle, &x, &y);
			return Math::Vec2(float(x), float(y));
		}

		void Window::setMousePosition(const Math::Vec2& pos) const {
			glfwSetCursorPos(windowHandle, pos.x, pos.y);
		}
	}
}