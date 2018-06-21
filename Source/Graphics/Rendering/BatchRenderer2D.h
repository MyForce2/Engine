#pragma once


#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/VertexArray.h"

namespace Engine {
	namespace Graphics {

		class BatchRenderer2D {
		private:
			VertexArray vao;
			IndexBuffer* ibo;
			VertexBuffer* vbo;
			unsigned short amountOfIndices;

			static const unsigned short VERTEX_SIZE = 8;
			static const unsigned short MAX_OBJECTS = 10000;
			static const unsigned short INDICES_PER_OBJECT = 6;
			static const unsigned int INDEX_BUFFER_SIZE = INDICES_PER_OBJECT * MAX_OBJECTS;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void start();
			void end();

			void add(const float* vertices, const float* uvCoords);
			void flush();
		};
	}
}
