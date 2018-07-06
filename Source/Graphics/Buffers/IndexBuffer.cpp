#pragma once

#include "IndexBuffer.h"

namespace Engine {
	namespace Graphics {

		IndexBuffer::IndexBuffer() : count(0U) {
			glGenBuffers(1, &id);
		}

		IndexBuffer::IndexBuffer(const GLushort* data, size_t size) : count(size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			unBind();
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &id);
			unBind();
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		void IndexBuffer::unBind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}