#include "BatchRenderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <Utils/stb_image_write.h>



namespace Engine {
	namespace Graphics {

		
		using namespace Math;

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
			Tg::FontDescription fontDescription("arial.ttf", FONT_SIZE);
			Tg::FontGlyphRange glyphRange((char) 32, (char) 127);
			font = Tg::BuildFont(fontDescription, glyphRange, 4U);
			auto img = font.image;
			stbi_write_png("FontAtlas.png", img.GetSize().width, img.GetSize().height, 1, img.GetImageBuffer().data(), img.GetSize().width);
			fontAtlas = new Texture("FontAtlas.png", GL_LINEAR);
		}
		
		void BatchRenderer::start() {
			vbo->bind();
			data = (BatchVertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer::end() {
			vbo->bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		void BatchRenderer::drawText(const std::string& text, Vec2 position, unsigned int fontSize) {
			float imageHeight = font.image.GetSize().height;
			float imageWidth = font.image.GetSize().width;
			for (int i = 0; i < text.length(); i++) {
				Tg::FontGlyph glyph = font.glyphSet[text[i]];
				// The picture is flipped when loaded so its needed to get the size - top / bottom for the correct positions
				float top = imageHeight - glyph.rect.top;
				float bottom = imageHeight - glyph.rect.bottom;
				float ratio = ((float) FONT_SIZE) / fontSize;
				Vec2 topRightUV = Vec2(glyph.rect.right / imageWidth, top / imageHeight);
				Vec2 bottomLeftUV = Vec2(glyph.rect.left / imageWidth, bottom / imageHeight);
				int yOffset = (glyph.height - glyph.yOffset) / ratio;
				float width = glyph.width / ratio;
				float height = glyph.height / ratio;
				data->position = Vec2(position.x + width, position.y + height - yOffset);
				data->uvCoords = Vec2(topRightUV.x, topRightUV.y);
				data++;
				data->position = Vec2(position.x, position.y + height - yOffset);
				data->uvCoords = Vec2(bottomLeftUV.x, topRightUV.y);
				data++;
				data->position = Vec2(position.x, position.y - yOffset);
				data->uvCoords = Vec2(bottomLeftUV.x, bottomLeftUV.y);
				data++;
				data->position = Vec2(position.x + width,  position.y - yOffset);
				data->uvCoords = Vec2(topRightUV.x, bottomLeftUV.y);
				data++;
				position.x += glyph.advance / ratio;
			}
			amountOfIndices += 6 * text.length();
		}

		void BatchRenderer::flush() {
			vbo->bind();
			vao.bind();
			ibo->bind();
			fontAtlas->setSlot();
			glDrawElements(GL_TRIANGLES, amountOfIndices, GL_UNSIGNED_SHORT, nullptr);
			amountOfIndices = 0U;
			vbo->unBind();
			vao.unBind();
			ibo->unBind();
		}
	}
}