#pragma once

#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderable2DTexture.h"
#include "Math/Vec2.h"
#include <Typo/Typo.h>

#include <array>


namespace Engine {
	namespace Graphics {

		// A struct depicting the structure of a vertex
		struct BatchVertex {
			Math::Vec2 position;
			Math::Vec2 uvCoords;
			GLfloat textureSlot;
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
			BatchVertex* data;
			GLsizei amountOfIndices;
			Texture* fontAtlas;
			Tg::FontModel font;

			std::array<GLuint, 10> textureSlots;

			
			static const unsigned int FONT_SIZE = 192;
			static const unsigned short INDICES_PER_OBJECT = 6;
			static const unsigned short MAX_OBJECTS = 10000;
			static const unsigned short IBO_SIZE = INDICES_PER_OBJECT * MAX_OBJECTS;
			static const unsigned int VBO_SIZE = sizeof(BatchVertex) * MAX_OBJECTS;

		public:
			BatchRenderer();
			~BatchRenderer();

			void init();
			void start();
			void end();
			void flush();

			// Draws the requested text, at the given position
			void drawText(const std::string& text, Math::Vec2 startPosition, unsigned int fontSize);
			void add(const Renderable2DTexture& object);

		private:
			GLfloat addTexture(const Texture& texture);
		};
	}
}
