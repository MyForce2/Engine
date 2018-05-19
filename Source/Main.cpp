#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace Engine;
using namespace Math;
using namespace Graphics;

static const int WIDTH = 1280;
static const int HEIGHT = 720;



struct Timer {

	std::chrono::time_point<std::chrono::steady_clock> start;

	Timer() {
		 start = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		std::cout << duration.count() * 1000 << " ms" << std::endl;
	}
};


void test(Mat4& model, float angle, float tUnit) {
	model = Mat4::translation(Vec3(-tUnit, -tUnit, 0.f)) * model;
	model = Mat4::rotationZ(angle) * model;
	model = Mat4::translation(Vec3(tUnit, tUnit, 0.f)) * model;
}




int main() {
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	float positions[] = {
		600.f, 600.f,
		600.f, 500.f,
		500.f, 500.f,
		500.f, 600.f
	};

	float texCoords[] = {
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	VBLayout layout;
	layout.addElement(2, GL_FLOAT);
	VertexBuffer vbo(positions, sizeof(positions));
	VertexBuffer tex(texCoords, sizeof(texCoords));
	vao.addBuffer(vbo, layout);
	vao.addBuffer(tex, layout);
	IndexBuffer ibo(indices, 6);
	Texture texture("Resources/Textures/Texture.png");
	Shader shader("Resources/Shaders/Vertex.shader", "Resources/Shaders/Fragment.shader");
	texture.setSlot();
	shader.setUniform1i("u_TextureSlot", 0);

	float w = (float) WIDTH;
	float h = (float) HEIGHT;
	Mat4 projection = Mat4::orthographic(0.f, w, 0.f, h, -1.f, 1.f);
	Mat4 model(1.f);
	Mat4 view(1.f);

	test(model, 45.f, 550.f);
	shader.setUniformMatrix4fv("u_Projection", projection);
	shader.setUniformMatrix4fv("u_Model", model);
	shader.setUniformMatrix4fv("u_View", view);

	vao.bind();
	ibo.bind();
	shader.bind();


	float perSec = 180.f;
	while (!window.isClosed() && !window.isKeyPressed(GLFW_KEY_ESCAPE)) {
		shader.setUniformMatrix4fv("u_Model", model);
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		shader.setUniformMatrix4fv("u_Model", Mat4(1.f));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);

		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}