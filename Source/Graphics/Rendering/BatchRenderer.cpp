#include "BatchRenderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <Utils/stb_image_write.h>



namespace Engine {
	namespace Graphics {

		
		using namespace Math;

		struct RenderableVertex {
			Math::Vec2 position;
			Math::Vec2 uv;
		};

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
			layout.addElement(1, GL_FLOAT);
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
			Tg::Image img = font.image;
			stbi_write_png("FontAtlas.png", img.GetSize().width, img.GetSize().height, 1, img.GetImageBuffer().data(), img.GetSize().width);
			fontAtlas = new Texture("FontAtlas.png", GL_LINEAR);
		}
		
		void BatchRenderer::start() {
			vbo->bind();
			textureSlots.fill(0);
			addTexture(*fontAtlas);
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
				float yOffset = (glyph.height - glyph.yOffset) / ratio;
				float width = glyph.width / ratio;
				float height = glyph.height / ratio;
				data->position = Vec2(position.x + width, position.y + height - yOffset);
				data->uvCoords = Vec2(topRightUV.x, topRightUV.y);
				data->textureSlot = 0.f;
				data++;
				data->position = Vec2(position.x, position.y + height - yOffset);
				data->uvCoords = Vec2(bottomLeftUV.x, topRightUV.y);
				data->textureSlot = 0.f;
				data++;
				data->position = Vec2(position.x, position.y - yOffset);
				data->uvCoords = Vec2(bottomLeftUV.x, bottomLeftUV.y);
				data->textureSlot = 0.f;
				data++;
				data->position = Vec2(position.x + width,  position.y - yOffset);
				data->uvCoords = Vec2(topRightUV.x, bottomLeftUV.y);
				data->textureSlot = 0.f;
				data++;
				position.x += glyph.advance / ratio;
			}
			amountOfIndices += 6 * text.length();
		}

		void BatchRenderer::add(const Renderable2DTexture& object) {
			RenderableVertex* objData = (RenderableVertex*) object.getVBO()->map(GL_READ_ONLY);
			GLfloat texSlot = addTexture(object.getTexture());
			for (int i = 0; i < 4; i++) {
				data->position = objData->position;
				data->uvCoords = objData->uv;
				data->textureSlot = texSlot;
				data++;
				objData++;
			}
			object.getVBO()->unMap();
			amountOfIndices += 6;
		}

		GLfloat BatchRenderer::addTexture(const Texture& texture) {
			GLuint texID = texture.getID();
			for (int i = 0; i < textureSlots.size(); i++) {
				if (textureSlots[i] == 0) {
					textureSlots[i] = texID;
					return (float)i;
				}
				if (textureSlots[i] == texID) 
					return (float)i;
			}
			/*end();
			flush();
			start();
			return addTexture(texture);*/
		}

		void BatchRenderer::flush() {
			vbo->bind();
			vao.bind();
			ibo->bind();
			for (int i = 0; i < textureSlots.size(); i++) {
				GLuint texID = textureSlots[i];
				if (texID == 0)
					break;
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, texID);
			}
			glDrawElements(GL_TRIANGLES, amountOfIndices, GL_UNSIGNED_SHORT, nullptr);
			amountOfIndices = 0U;
			vbo->unBind();
			vao.unBind();
			ibo->unBind();
		}
	}
}