#include "BatchRenderer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <Utils/stb_image_write.h>



namespace Engine {
	namespace Graphics {

		
		using namespace Math;
		const std::string BatchRenderer::FONT_ATLAS_PATH = "FontAtlas.png";
		const std::string BatchRenderer::FONT_PATH = "Times New Roman.ttf";

		// The vbo data for a Renderable2DTexture object, used for data mapping
		struct RenderableVertex {
			Math::Vec2 position;
			Math::Vec2 uv;
		};

		BatchRenderer::BatchRenderer() : amountOfObjects(0) {
			init();
		}

		BatchRenderer::~BatchRenderer() {
			delete ibo;
			delete vbo;
		}

		void BatchRenderer::init() {
			vbo = new VertexBuffer(VBO_SIZE, GL_DYNAMIC_DRAW);
			modelMatricesBuffer = new VertexBuffer(MATRICES_BUFFER_SIZE, GL_DYNAMIC_DRAW);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			layout.addElement(2, GL_FLOAT);
			layout.addElement(1, GL_INT);
			layout.addElement(1, GL_INT);
			layout.addElement(3, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
			vao.addMatrixBuffer(*modelMatricesBuffer);
			GLushort* indices = new GLushort[IBO_SIZE];
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
			delete[] indices;
			Tg::FontDescription fontDescription(FONT_PATH, FONT_SIZE);
			Tg::FontGlyphRange glyphRange((char) 32, (char) 127);
			font = Tg::BuildFont(fontDescription, glyphRange, 4U);
			Tg::Image img = font.image;
			stbi_flip_vertically_on_write(1);
			stbi_write_png(FONT_ATLAS_PATH.c_str(), img.GetSize().width, img.GetSize().height, 1, img.GetImageBuffer().data(), img.GetSize().width);
			fontAtlas = new Texture(FONT_ATLAS_PATH, GL_LINEAR);
		}
		
		void BatchRenderer::start() {
			textureSlots.fill(0);
			addTexture(*fontAtlas);
			data = (BatchVertex*) vbo->map(GL_WRITE_ONLY);
			modelMatrices = (Math::Mat4*) modelMatricesBuffer->map(GL_WRITE_ONLY);
		}

		void BatchRenderer::end() {
			vbo->unMap();
			modelMatricesBuffer->unMap();
		}


		void BatchRenderer::addText(const std::string& text, Vec2 position, unsigned int fontSize, const Math::Vec3& textColor, const Math::Mat4& model) {
			float imageHeight = float(font.image.GetSize().height);
			float imageWidth = float(font.image.GetSize().width);
			Vec3 normalizedColor(textColor);
			normalizedColor /= 255;
			for (unsigned int i = 0; i < text.length(); i++) {
				Tg::FontGlyph glyph = font.glyphSet[text[i]];
				float ratio = ((float) FONT_SIZE) / fontSize;
				Vec2 topRightUV = Vec2(glyph.rect.right / imageWidth, glyph.rect.top / imageHeight);
				Vec2 bottomLeftUV = Vec2(glyph.rect.left / imageWidth, glyph.rect.bottom / imageHeight);
				float yOffset = (glyph.height - glyph.yOffset) / ratio;
				float width = glyph.width / ratio;
				float height = glyph.height / ratio;

				data->position = Vec2(position.x + width, position.y + height - yOffset);
				data->uvCoords = Vec2(topRightUV.x, topRightUV.y);
				data->textureSlot = 0;
				data->isText = 1;
				data->textColor = normalizedColor;
				*modelMatrices = model;

				modelMatrices++;
				data++;

				data->position = Vec2(position.x, position.y + height - yOffset);
				data->uvCoords = Vec2(bottomLeftUV.x, topRightUV.y);
				data->textureSlot = 0;
				data->isText = 1;
				data->textColor = normalizedColor;
				*modelMatrices = model;

				modelMatrices++;
				data++;

				data->position = Vec2(position.x, position.y - yOffset);
				data->uvCoords = Vec2(bottomLeftUV.x, bottomLeftUV.y);
				data->textureSlot = 0;
				data->isText = 1;
				data->textColor = normalizedColor;
				*modelMatrices = model;

				modelMatrices++;
				data++;

				data->position = Vec2(position.x + width,  position.y - yOffset);
				data->uvCoords = Vec2(topRightUV.x, bottomLeftUV.y);
				data->textureSlot = 0;
				data->isText = 1;
				data->textColor = normalizedColor;
				*modelMatrices = model;

				modelMatrices++;
				data++;


				position.x += glyph.advance / ratio;
				\
			}
			amountOfObjects += text.length();
		}

		void BatchRenderer::addText(const Label& label) {
			addText(label.getText(), label.getStartPosition(), label.getFontSize(), label.getLabelColor(), label.getModelMatrix());
		}

		void BatchRenderer::add(const Renderable2DTexture& object) {
			RenderableVertex* objData = (RenderableVertex*) object.getVBO()->map(GL_READ_ONLY);
			GLint texSlot = addTexture(object.getTexture());
			for (int i = 0; i < 4; i++) {
				data->position = objData->position;
				data->uvCoords = objData->uv;
				data->textureSlot = texSlot;
				data->isText = 0;
				data->textColor = Vec4(0);
				*modelMatrices = object.getModelMatrix();
				
				modelMatrices++;
				data++;
				objData++;
			}
			object.getVBO()->unMap();
			amountOfObjects++;
		}

		GLint BatchRenderer::addTexture(const Texture& texture) {
			GLuint texID = texture.getID();
			for (unsigned int i = 0; i < textureSlots.size(); i++) {
				if (textureSlots[i] == 0) {
					textureSlots[i] = texID;
					return i;
				}
				if (textureSlots[i] == texID) 
					return i;
			}
			end();
			flush();
			start();
			return addTexture(texture);
		}

		void BatchRenderer::flush() {
			vbo->bind();
			vao.bind();
			ibo->bind();
			for (unsigned int i = 0; i < textureSlots.size(); i++) {
				GLuint texID = textureSlots[i];
				if (texID == 0)
					break;
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, texID);
			}
			glDrawElements(GL_TRIANGLES, amountOfObjects * 6, GL_UNSIGNED_SHORT, nullptr);
			amountOfObjects = 0U;
			vbo->unBind();
			vao.unBind();
			ibo->unBind();
		}
	}
}