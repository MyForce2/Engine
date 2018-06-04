#pragma once

#include <GL/glew.h>


#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

namespace Engine {
	namespace Graphics {

		class BasicRenderer {
		private:

		public:
			BasicRenderer();
			~BasicRenderer();

			void renderArraysInstanced(const VertexArray& vao, const Shader& shader, GLint first, GLsizei count, GLsizei instances) const;
			void renderArrays(const VertexArray& vao, const Shader& shader, GLint first, GLsizei count) const;
			void renderElementsInstanced(const VertexArray& vao, const Shader& shader, const IndexBuffer& ibo, GLsizei instances) const;
			void renderElements(const VertexArray& vao, const Shader& shader, const IndexBuffer& ibo) const;

		};

	}
}
