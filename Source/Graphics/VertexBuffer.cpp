
#include "VertexBuffer.h"
#include <memory>

namespace Engine {
	namespace Graphics {

		VertexBuffer::VertexBuffer(GLsizeiptr size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
			unBind();
		}

		VertexBuffer::VertexBuffer(GLsizeiptr size, GLenum usage) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);
			unBind();
		}

		VertexBuffer::VertexBuffer(const GLvoid* data, GLsizeiptr size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			unBind();
		}

		VertexBuffer::VertexBuffer(const GLvoid* data, GLsizeiptr size, GLenum usage) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
			unBind();
		}

		VertexBuffer::~VertexBuffer() {
			glDeleteBuffers(1, &id);
			unBind();
		}

		void VertexBuffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		void VertexBuffer::unBind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::setData(const GLvoid* data, GLsizeiptr size) {
			bind();
			GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			memcpy(buffer, data, size);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			unBind();
		}
	}
}