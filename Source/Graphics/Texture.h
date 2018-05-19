#pragma once

#include <string>

#include "GL\glew.h"


namespace Engine {
	namespace Graphics {

		class Texture {
		private:
			GLuint id;

		public:
			Texture(const std::string& path);
			Texture(const char* path);
			~Texture();

			void setSlot(unsigned int slot = 0) const;
			void unBind() const;
		};
	}
}