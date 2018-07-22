#pragma once

#include "IndexBuffer.h"

namespace Engine {
	namespace Graphics {

		IndexBuffer::IndexBuffer() : count(0U) {
			glGenBuffers(1, &id);
		}

		IndexBuffer::IndexBuffer(const GLushort* data, unsigned short size) : count(size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			unBind();
		}

		IndexBuffer::IndexBuffer(const GLushort* data, unsigned short size, GLenum access) : count(size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, access);
			unBind();
		}

		IndexBuffer::IndexBuffer(const IndexBuffer& ibo) : count(ibo.count) {
			glGenBuffers(1, &id);
			GLint usage;
			ibo.bind();
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);
			GLvoid* data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_READ_ONLY);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, usage);
			ibo.bind();
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			ibo.unBind();

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

		GLvoid* IndexBuffer::map(GLenum access) const {
			bind();
			GLvoid* data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, access);
			unBind();
			return data;
		}

		void IndexBuffer::unMap() const {
			bind();
			glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
			unBind();
		}
	}
}