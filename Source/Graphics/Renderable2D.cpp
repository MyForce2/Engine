#include "Renderable2D.h"

namespace Engine {
	namespace Graphics {


		Renderable2D::Renderable2D(const GLvoid* data, GLsizeiptr size) : modelMatrix(1.f) {
			vbo = new VertexBuffer(data, size);
			GLushort indices[]= {
				0, 1, 2,
				0, 2, 3
			};
			ibo = new IndexBuffer(indices, 6);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
		}

		Renderable2D::Renderable2D(const GLvoid* data, GLsizeiptr size, const Math::Mat4& modelMatrix) : modelMatrix(modelMatrix) {
			vbo = new VertexBuffer(data, size);
			GLushort indices[] = {
				0, 1, 2,
				0, 2, 3
			};
			ibo = new IndexBuffer(indices, 6);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
		}

		Renderable2D::Renderable2D() : modelMatrix(1.f), vbo(nullptr) {
			GLushort indices[] = {
				0, 1, 2,
				0, 2, 3
			};
			ibo = new IndexBuffer(indices, 6);
		}

		Renderable2D::~Renderable2D() {
			if (vbo != nullptr)
				delete vbo;
			delete ibo;
		}
	}
}