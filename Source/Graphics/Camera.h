#pragma once

#include "Math\Mat4.h"
#include "Math\Vec3.h"
#include "Window.h"

namespace Engine {
	namespace Graphics {

		/*
		A class that used to simulate a FPS 3D camera
		*/
		class Camera {
		private:
			// The camera's position in space (Player position)
			Math::Vec3 position;
			// The direction the camera is looking at
			Math::Vec3 viewingDirection;
			// The up direction in world space (Default is (0, 1, 0))
			Math::Vec3 upDirection;
			// Euler angle, depicts how much the camera is looking up or down
			float pitch;
			// Euler angle, depicte how much the camera is looking right or left 
			float yaw;
			// The mouse sensitivity (How much does the camera move for a certain mouse movement)
			static const float sensitivity;

		public:
			Camera();
			~Camera();

			// Sets the camera position in world space
			void setPosition(const Math::Vec3& position);
			// Sets the viewing direction in world space
			void setViewingDirection(const Math::Vec3& direction);
			inline const Math::Vec3& getPosition() const { return position; }
			inline const Math::Vec3& getViewingDirection() const { return viewingDirection; }

			// Generates the view matrix, according to the position and viewDirection
			Math::Mat4 generateViewMatrix() const;
			// Updates the viewingDirection vector, (recalculates it according to mouse movement)
			void updateViewDirection(const Window& window);
		};
	}
}
