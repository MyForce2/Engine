
#include "VertexBuffer.h"
#include <memory>

namespace Engine {
	namespace Graphics {

		VertexBuffer::VertexBuffer() {
			glGenBuffers(1, &id);
		}

		VertexBuffer::VertexBuffer(const void* data, size_t size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
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

		void VertexBuffer::setData(const void* data, size_t size) {
			bind();
			GLvoid* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			memcpy(buffer, data, size);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			unBind();
		}
	}
}