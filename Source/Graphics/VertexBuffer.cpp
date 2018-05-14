
#include "VertexBuffer.h"

namespace Engine {
	namespace Graphics {

		VertexBuffer::VertexBuffer() {
			glGenBuffers(1, &id);
			bind();
		}

		VertexBuffer::VertexBuffer(const void* data, size_t size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		VertexBuffer::~VertexBuffer() {
			glDeleteBuffers(1, &id);
		}

		void VertexBuffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		void VertexBuffer::unBind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}