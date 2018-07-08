#pragma once

#include <string>

#include "GL\glew.h"


namespace Engine {
	namespace Graphics {
		
		/*
		A class that represent a 2D texture and handles its creation and deletion
		*/

		class Texture {
		private:
			GLuint id;

		public:
			Texture(const std::string& path);
			Texture(const char* path);
			Texture(const std::string& path, GLint filterParam);
			Texture(const char* path, GLint filterParam);
			~Texture();

			// Binds this texture to the given slot, default slot is 0
			void setSlot(unsigned int slot = 0) const;
			// Unbinds this texture
			void unBind() const;

			inline const GLuint getID() const { return id; }
		};
	}
}