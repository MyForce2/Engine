#pragma once

#include "UniformBuffer.h"

#include <memory>

namespace Engine {
	namespace Graphics {

		UniformBuffer::UniformBuffer() {
			glGenBuffers(1, &id);
		}

		UniformBuffer::UniformBuffer(GLvoid* data, GLsizeiptr size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
			unBind();
		}

		UniformBuffer::UniformBuffer(GLvoid* data, GLsizeiptr size, GLenum usage) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
			unBind();
		}

		UniformBuffer::UniformBuffer(const UniformBuffer& ubo) {
			glGenBuffers(1, &id);
			copyBuffer(ubo);
		}

		UniformBuffer::UniformBuffer(UniformBuffer&& ubo) : id(ubo.id) {
			ubo.id = 0;
		}
		
		UniformBuffer::~UniformBuffer() {
			glDeleteBuffers(1, &id);
			unBind();
		}

		void UniformBuffer::bind() const {
			glBindBuffer(GL_UNIFORM_BUFFER, id);
		}

		void UniformBuffer::unBind() const {
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		GLvoid* UniformBuffer::map(GLenum access) const {
			bind();
			GLvoid* data = glMapBuffer(GL_UNIFORM_BUFFER, access);
			unBind();
			return data;
		}

		void UniformBuffer::unMap() const {
			bind();
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			unBind();
		}

		void UniformBuffer::operator=(UniformBuffer&& ubo) {
			glDeleteBuffers(1, &id);
			id = ubo.id;
			ubo.id = 0;
		}

		void UniformBuffer::operator=(const UniformBuffer& ubo) {
			glDeleteBuffers(1, &id);
			glGenBuffers(1, &id);
			copyBuffer(ubo);
		}

		void UniformBuffer::copyBuffer(const UniformBuffer& ubo) {
			GLint size, usage;
			ubo.bind();
			glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_USAGE, &usage);
			GLvoid* data = glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_ONLY);
			bind();
			glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
			ubo.bind();
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			ubo.unBind();
		}
	}
}