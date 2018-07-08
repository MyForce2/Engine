#pragma once

#include <GL\glew.h>

namespace Engine {
	namespace Graphics {
		 
		/*
		A class that represent a simple VertexBuffer and handles its creation and deletion
		*/
		class VertexBuffer {
		private:
			GLuint id;
			
		public:
			VertexBuffer(GLsizeiptr size);
			VertexBuffer(GLsizeiptr size, GLenum usage);
			VertexBuffer(const VertexBuffer& vbo);

			// Size in bytes
			VertexBuffer(const GLvoid* data, GLsizeiptr size);
			VertexBuffer(const GLvoid* data, GLsizeiptr size, GLenum usage);

			VertexBuffer(VertexBuffer&& vbo) = delete;

			~VertexBuffer();


			// Binds this buffer
			void bind() const;
			// Unbinds this buffer
			void unBind() const;
			// Refill this buffer with new data
			void setData(const GLvoid* data, GLsizeiptr size);

			inline GLuint getID() const { return id; }
		};
	}
}