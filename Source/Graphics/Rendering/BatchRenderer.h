#pragma once

#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Renderable2D.h"
#include "Graphics/Renderable2DTexture.h"
#include "Graphics/Label.h"
#include "Math/Vec2.h"
#include <Typo/Typo.h>

#include <array>


namespace Engine {
	namespace Graphics {

		// The data of a vertex inside the vbo
		struct BatchVertex {
			// The vertex position
			Math::Vec2 position;
			// The vertex uv coordinates
			Math::Vec2 uvCoords;
			// The vertex textureSlot in the texture slots array
			GLint textureSlot;
			// A boolean variable, GLSL doesn't support bool attributes / variants
			GLint isText;
			// Text color, if the object is text
			Math::Vec4 textColor;
		};
		
		/* 
		A special type of renderer that is used to render multiple instances of the same object type (2D, 4 Vertices texture)
		using one big vertex buffer and one big index buffer
		*/
		class BatchRenderer {
		private:
			IndexBuffer* ibo;
			VertexBuffer* vbo;
			VertexArray vao;

			// A pointer to the vbo data
			BatchVertex* data;
			// The amount of vertices to render in the next draw call
			GLsizei amountOfIndices;
			// The actual font atlas texture
			Texture* fontAtlas;
			// The font atlas data
			Tg::FontModel font;
			// 10 Texture slots dedicated for the batch renderer
			std::array<GLuint, 10> textureSlots;

			
			static const unsigned int FONT_SIZE = 192;
			static const unsigned short INDICES_PER_OBJECT = 6;
			static const unsigned short MAX_OBJECTS = 10000;
			static const unsigned short IBO_SIZE = INDICES_PER_OBJECT * MAX_OBJECTS;
			static const unsigned int VBO_SIZE = sizeof(BatchVertex) * MAX_OBJECTS;
			static const std::string FONT_ATLAS_PATH;

		public:
			BatchRenderer();
			~BatchRenderer();

			// Clears all past data, maps the buffer to the begining, must call before adding objects
			void start();
			// Unmaps the buffer, must call after all of the objects have been added
			void end();
			// Draws all of the objects added after the previous flush, or from the creation of the object if flush wasn't called before
			void flush();

			// Adds the requested text, at the given position
			void addText(const std::string& text, const Math::Vec2& startPosition, unsigned int fontSize);
			// Adds the requested text, at the given position
			void addText(const std::string& text, Math::Vec2 startPosition, unsigned int fontSize, const Math::Vec3& textColor);
			// Adds the request label
			void addText(const Label& label);
			// Adds this object
			void add(const Renderable2DTexture& object);

		private:
			// Inits all of the renderer members
			void init();
			// Adds a texture to the texture slots, or return its index in the texture slots array if it was already added
			GLint addTexture(const Texture& texture);
		};
	}
}
