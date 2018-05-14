#pragma once

#include <string>

#include "Math\Vec2.h"

namespace Engine {
	namespace Graphics {
		 
		class Window {
		private:
			int height, width;
			std::string title;
			Math::Vec2 mousePosition;
			GLFWwindow* windowHandle;

		public:
			Window(const std::string& title, int height, int width);
			~Window();

			bool isClosed() const;
			bool isKeyPressed(int key) const;
			bool isKeyReleased(int key) const;

			void update();

			inline const Math::Vec2& getMousePosition() const { return  mousePosition; }
			
		private:
			void updateMousePosition();
		};
	}
}