#pragma once

#include "UniformBuffer.h"

#include <memory>

namespace Engine {
	namespace Graphics {

		UniformBuffer::UniformBuffer() {
			glGenBuffers(1, &id);
		}

		UniformBuffer::UniformBuffer(const void* data, size_t size) {
			glGenBuffers(1, &id);
			bind();
			glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
		}

		UniformBuffer::UniformBuffer(const UniformBuffer& ubo) {
			glGenBuffers(1, &id);
			GLint size, usage;
			ubo.bind();
			glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_USAGE , &usage);
			GLvoid* data = glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_ONLY);
			bind();
			glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
			ubo.bind();
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			ubo.unBind();
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

		void UniformBuffer::setData(const void* data) {
			bind();
			GLint size;
			glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &size);
			GLvoid* buffer = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(buffer, data, size);
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			unBind();
		}
	}
}