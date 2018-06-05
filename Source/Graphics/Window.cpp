#pragma once

#include "FrameBuffer.h"
#include <GLFW\glfw3.h>

#include "Window.h"
#include "Utils\Log.h"


namespace Engine {
	namespace Graphics {

		Window::Window(const std::string& title, int height, int width, GLbitfield clearMask) : title(title), height(height), width(width), clearMask(clearMask) {
			if (!glfwInit())
				Utils::Log::getLog()->logError("Failed to init glfw");
			glfwWindowHint(GLFW_SAMPLES, 4);
			windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (!windowHandle)
				Utils::Log::getLog()->logError("Failed to create window");
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

		bool Window::isMouseButtonPressed(int button) const {
			return glfwGetMouseButton(windowHandle, button) == GLFW_PRESS;
		}

		bool Window::isMouseButtonReleased(int button) const {
			return glfwGetMouseButton(windowHandle, button) == GLFW_RELEASE;
		}

		void Window::update() {
			glfwGetWindowSize(windowHandle, &width, &height);
			glfwSwapBuffers(windowHandle);
			glfwPollEvents();
			FrameBuffer::clearBuffer(clearMask);
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