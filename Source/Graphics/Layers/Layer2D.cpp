#include "Layer2D.h"

namespace Engine {
	namespace Graphics {

		const float Layer2D::PROJECTION_TOP = 800.f;
		const float Layer2D::PROJECTION_LEFT = 600.f;
		const int Layer2D::MAX_TEXTURE_UNITS = 10;

		Layer2D::Layer2D(float top, float right, const std::string& vertex, const std::string& fragment) : shader(vertex, fragment),
			projection(Math::Mat4::orthographic(0.f, right, 0.f, top)), view(1.f) {
			initShader();
		}

		Layer2D::Layer2D(const std::string& vertex, const std::string& fragment) : shader(vertex, fragment),
			projection(Math::Mat4::orthographic(0.f, PROJECTION_TOP, 0.f, PROJECTION_LEFT)), view(1.f) {
			initShader();
		}

		Layer2D::Layer2D(const Math::Mat4& projection, const std::string& vertex, const std::string& fragment) : 
			shader(vertex, fragment), projection(projection), view(1.f) {
			initShader();
		}

		void Layer2D::add(Label& label) {
			label.generateVerticesData();
			renderer.addText(label);
		}

		void Layer2D::add(const Renderable2DTexture& renderable) {
			renderer.add(renderable);
		}

		void Layer2D::setProjection(const Math::Mat4& projection) {
			this->projection = projection;
			shader.setUniformMatrix4fv("projection", projection);
		}

		void Layer2D::setView(const Math::Mat4& view) {
			this->view = view;
			shader.setUniformMatrix4fv("view", view);
		}

		void Layer2D::startFrame() {
			renderer.start();
		}

		void Layer2D::render() {
			renderer.end();
			shader.bind();
			glDisable(GL_DEPTH_TEST);
			renderer.flush();
			glEnable(GL_DEPTH_TEST);
		}

		void Layer2D::initShader() {
			shader.setUniformMatrix4fv("projection", projection);
			shader.setUniformMatrix4fv("view", view);
			for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
				shader.setInt("u_TexSlots[" + std::to_string(i) + "]", i);
			}
		}
	}
}