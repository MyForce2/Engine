#pragma once

#include "Buffers/VertexBuffer.h"
#include "Buffers/IndexBuffer.h"
#include "VertexArray.h"
#include "Math/Mat4.h"

namespace Engine {
	namespace Graphics {


		class Renderable2D {
		protected:
			IndexBuffer* ibo;
			VertexBuffer* vbo;
			VertexArray vao;
			Math::Mat4 model;

		public:
			Renderable2D(const GLvoid* data, GLsizeiptr dataSize);
			Renderable2D();
			virtual ~Renderable2D();

			inline const IndexBuffer* getIBO() const { return ibo; }
			inline const VertexBuffer* getVBO() const { return vbo; }
			inline const VertexArray& getVAO() const { return vao; }
		};
	}
}