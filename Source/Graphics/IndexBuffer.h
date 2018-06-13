#pragma once

#include <GL\glew.h>

namespace Engine {
	namespace Graphics {

		/*
		A class that represent an index buffer
		*/
		class IndexBuffer {
		private:
			GLuint id;
			// The amount of indices
			unsigned int count;

		public:
			IndexBuffer();
			IndexBuffer(const GLushort* data, size_t size);
			~IndexBuffer();

			// Binds this buffer
			void bind() const;
			// Unbinds this buffer
			void unBind() const;

			inline GLuint getID() const { return id; };
			inline GLuint getCount() const { return count; };
		};
	}
}
