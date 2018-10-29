#include "BatchRenderer.h"
#include "Utils/Log.h"



namespace Engine {
	namespace Graphics {

		
		using namespace Math;

		const unsigned short BatchRenderer::INDICES_PER_OBJECT = 6;
		const unsigned short BatchRenderer::MAX_OBJECTS = 10000;
		const unsigned short BatchRenderer::IBO_SIZE = BatchRenderer::INDICES_PER_OBJECT * BatchRenderer::MAX_OBJECTS;
		const unsigned int BatchRenderer::VBO_SIZE = sizeof(BatchVertex) * 4 * BatchRenderer::MAX_OBJECTS;

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
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			layout.addElement(2, GL_FLOAT);
			layout.addElement(1, GL_INT);
			layout.addElement(1, GL_INT);
			layout.addElement(3, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
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
			Utils::Log::getLog()->logInfo("Batch Renderer initialized");
		}
		
		void BatchRenderer::start() {
			textureSlots.fill(0);
			data = (BatchVertex*) vbo->map(GL_WRITE_ONLY);
		}

		void BatchRenderer::end() {
			vbo->unMap();
		}


		void BatchRenderer::addText(const Label& label) {
			GLint texSlot = addTexture(label.getFont()->getFontAtlas());
			const std::vector<LabelVertex>& vertices = label.getData();
			const std::string text = label.getText();
			for (unsigned int i = 0; i < text.size(); i++) {
				for (int j = 0; j < 4; j++) {
					const LabelVertex& vertex = vertices[i * 4 + j];
					data->position = vertex.position;
					data->uvCoords = vertex.uv;
					data->textureSlot = texSlot;
					data->isText = 1;
					data->textColor = vertex.color;
					data++;
				}

			}
			amountOfObjects += text.length();
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