
#include "BatchRenderer2D.h"


namespace Engine {
	namespace Graphics {

		BatchRenderer2D::BatchRenderer2D() {
			vbo = new VertexBuffer(MAX_OBJECTS * VERTEX_SIZE, GL_DYNAMIC_DRAW);
			VBLayout bufferLayout;
			bufferLayout.addElement(2, GL_FLOAT);
			bufferLayout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, bufferLayout);
			GLushort* indicesData = new GLushort[INDEX_BUFFER_SIZE];
			unsigned short offset = 0U;
			for (int i = 0; i < INDEX_BUFFER_SIZE; i += 6) {
				indicesData[i] = offset;
				indicesData[i + 1] = 1 + offset;
				indicesData[i + 2] = 2 + offset;
				indicesData[i + 3] = offset;
				indicesData[i + 4] = 2 + offset;
				indicesData[i + 5] = 3 + offset;

				offset += 4;
			}
			ibo = new IndexBuffer(indicesData, INDEX_BUFFER_SIZE);
			delete[] indicesData;
		}

		BatchRenderer2D::~BatchRenderer2D() {
			delete vbo;
			delete ibo;
		}

		void BatchRenderer2D::start() {
			vbo->bind();
			glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}



		
	}
}