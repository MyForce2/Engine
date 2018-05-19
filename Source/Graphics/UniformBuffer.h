#pragma once

#include <string>

#include "GL\glew.h"

namespace Engine {
	namespace Graphics {

		/*
		A class that represent a Uniform Buffer Object and handles its creation and deletion 
		and manages its data
		*/
		class UniformBuffer {
		private:
			GLuint id;

		public:
			UniformBuffer();
			// size in bytes
			UniformBuffer(const void* data, size_t size);
			~UniformBuffer();

			// Binds this buffer
			void bind() const;
			// Unbinds this buffer
			void unBind() const;

			// Sets the data of this uniform buffer, size in bytes
			void setData(const void* data, size_t size);

			inline GLuint getID() const { return id; }
			
		};
	}
}
