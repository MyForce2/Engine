#pragma once

#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexBuffer.h"
#include "../VertexArray.h"
#include "../Renderable2D.h"
#include "Math/Vec2.h"


namespace Engine {
	namespace Graphics {

		// A struct depicting the structure of a vertex
		struct Vertex {
			Math::Vec2 position;
		};
		
		/* 
		A special type of renderer that is used to render multiple instances of the same object
		using one big vertex buffer and one big index buffer
		*/
		class BatchRenderer {
		private:
			IndexBuffer* ibo;
			VertexBuffer* vbo;
			VertexArray vao;
			Vertex* data;
			GLsizei amountOfIndices;

			static const unsigned short INDICES_PER_OBJECT = 6;
			static const unsigned short MAX_OBJECTS = 10000;
			static const unsigned short IBO_SIZE = INDICES_PER_OBJECT * MAX_OBJECTS;
			static const unsigned int VBO_SIZE = sizeof(Vertex) * MAX_OBJECTS;

		public:
			BatchRenderer();
			~BatchRenderer();

			void init();

			void start();
			void end();

			void add(const Renderable2D& object);
			void flush();

		};
	}
}
