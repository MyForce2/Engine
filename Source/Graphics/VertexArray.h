#pragma once

#include <GL\glew.h>
#include "Buffers/VertexBuffer.h"
#include "VBLayout.h"

namespace Engine {
	namespace Graphics {
		/*
		A class used to represent a vertex array
		*/
		class VertexArray {
		private:
			GLuint id;
			// The amount of enabled attributes
			unsigned int amountOfAttributes;

		public:
			VertexArray();
			~VertexArray();

			void bind() const;
			void unBind() const;

			void addBuffer(const VertexBuffer& vbo, const VBLayout& layout);
			void addMatrixBuffer(const VertexBuffer& vbo);
			void addInstancedMatrixBuffer(const VertexBuffer& vbo);
		};
	}
}