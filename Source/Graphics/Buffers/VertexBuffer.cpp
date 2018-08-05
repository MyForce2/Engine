
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

		VertexBuffer::VertexBuffer(const VertexBuffer& vbo) {
			glGenBuffers(1, &id);
			copyBuffer(vbo);
		}

		VertexBuffer::VertexBuffer(VertexBuffer&& vbo) : id(vbo.id) {
			vbo.id = 0;
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

		GLvoid* VertexBuffer::map(GLenum access) const {
			bind();
			GLvoid* data =  glMapBuffer(GL_ARRAY_BUFFER, access);
			unBind();
			return data;
		}

		void VertexBuffer::unMap() const {
			bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
			unBind();
		}

		void VertexBuffer::operator=(VertexBuffer&& vbo) {
			glDeleteBuffers(1, &id);
			id = vbo.id;
			vbo.id = 0;
		}

		void VertexBuffer::operator=(const VertexBuffer& vbo) {
			glDeleteBuffers(1, &id);
			glGenBuffers(1, &id);
			copyBuffer(vbo);
		}

		void VertexBuffer::copyBuffer(const VertexBuffer& vbo) {
			GLint size, usage;
			vbo.bind();
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);
			GLvoid* data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
			bind();
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
			vbo.bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
			vbo.unBind();
		}


	}
}