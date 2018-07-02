#include "Renderable2D.h"

namespace Engine {
	namespace Graphics {


		Renderable2D::Renderable2D(const GLvoid* data, GLsizeiptr size) : model(1.f) {
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

		Renderable2D::Renderable2D() : model(1.f) {
			GLushort indices[] = {
				0, 1, 2,
				0, 2, 3
			};
			ibo = new IndexBuffer(indices, 6);
		}

		Renderable2D::~Renderable2D() {
			delete vbo;
			delete ibo;
		}
	}
}