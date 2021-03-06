#pragma once

#include "Buffers/FrameBuffer.h"
#include <GLFW\glfw3.h>
#include <Windows.h>

#include "Window.h"
#include "Utils\Log.h"


namespace Engine {
	namespace Graphics {

		

		Window::Window(const std::string& title, int height, int width, GLbitfield clearMask) : title(title), height(height), width(width), clearMask(clearMask) {
			if (!glfwInit())
				Utils::Log::getLog()->logError("Failed to init glfw");
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_RESIZABLE, false);			
			windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (!windowHandle)
				Utils::Log::getLog()->logError("Failed to create window");
			glfwMakeContextCurrent(windowHandle);
			glfwSwapInterval(0);
			glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			setMousePosition(getSize() / 2);
			glfwSetClipboardString(windowHandle, "Hello");
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

		bool Window::isCapsLockOn() const {
			return GetKeyState(VK_CAPITAL) & 1;
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

		void Window::setSize(const Math::Vec2& vec) {
			height = vec.y;
			width = vec.x;
			glfwSetWindowSize(windowHandle, vec.x, vec.y);
		}

		void Window::setFullScreen(bool fullScreen) {
			if (fullScreen)
				glfwSetWindowMonitor(windowHandle, glfwGetPrimaryMonitor(), 0, 0, width, height, REFRESH_RATE);
			else
				glfwSetWindowMonitor(windowHandle, glfwGetPrimaryMonitor(), NO_MONITOR_OFFSET, NO_MONITOR_OFFSET, width, height, REFRESH_RATE);
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