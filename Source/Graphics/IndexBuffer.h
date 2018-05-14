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
			unsigned int count;

		public:
			IndexBuffer();
			IndexBuffer(const unsigned int* data, size_t size);
			~IndexBuffer();

			void bind() const;
			void unBind() const;

			inline GLuint getID() const { return id; };
			inline GLuint getCount() const { return count; };
		};
	}
}
