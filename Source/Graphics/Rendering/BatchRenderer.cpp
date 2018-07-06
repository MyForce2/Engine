#include "BatchRenderer.h"

namespace Engine {
	namespace Graphics {


		BatchRenderer::BatchRenderer() : amountOfIndices(0U) {
			init();
		}

		BatchRenderer::~BatchRenderer() {
			delete ibo;
			delete vbo;
		}

		void BatchRenderer::init() {
			vbo = new VertexBuffer(VBO_SIZE, GL_DYNAMIC_DRAW);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
			GLushort indices[IBO_SIZE];
			int offset = 0;
			for (int i = 0; i < IBO_SIZE; i += 6) {
				indices[i] = offset;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset;
				indices[i + 4] = offset + 2;
				indices[i + 5] = offset + 3;

				offset += 4;
			}
			ibo = new IndexBuffer(indices, IBO_SIZE);
		}
		
		void BatchRenderer::start() {
			vbo->bind();
			data = (Vertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::end() {
			vbo->bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		void BatchRenderer::add(const Renderable2D& object) {
			object.getVBO()->bind();
			Vertex* objectData = (Vertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
			memcpy(data, objectData, sizeof(Vertex) * 4);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			object.getVBO()->unBind();
			data += 4;
			amountOfIndices += 6;
		}

		void BatchRenderer::flush() {
			vbo->bind();
			vao.bind();
			ibo->bind();
			glDrawElements(GL_TRIANGLES, amountOfIndices, GL_UNSIGNED_SHORT, nullptr);
			amountOfIndices = 0U;
			vbo->unBind();
			vao.unBind();
			ibo->unBind();
		}
	}
}