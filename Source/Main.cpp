#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include "Utils\Clock.h"
#include "Graphics\Camera2D.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace Engine;
using namespace Math;
using namespace Graphics;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

static const int WIDTH = 1280;
static const int HEIGHT = 720;
static const float ANGLE_PER_MSEC = 60.f;



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




void test(Mat4& model, float time, float tUnit) {
	Vec3 trans = Vec3(tUnit, tUnit, 0.f);
	float angle = time * ANGLE_PER_MSEC;
	model = Mat4::translation(trans * -1) * model;
	model = Mat4::rotationZ(angle) * model;
	model = Mat4::translation(trans) * model;
}


struct CameraData {
	Mat4 view;
	Mat4 projection;
};


void handleMove(const Window& window, Camera2D& camera, float time) {
	float speed = 250.f * time;
	if (window.isKeyPressed(GLFW_KEY_A)) 
		camera.move(Vec3(speed, 0.f, 0.f));
	if (window.isKeyPressed(GLFW_KEY_D))
		camera.move(Vec3(-speed, 0.f, 0.f));
	if (window.isKeyPressed(GLFW_KEY_S))
		camera.move(Vec3(0.f, speed, 0.f));
	if (window.isKeyPressed(GLFW_KEY_W))
		camera.move(Vec3(0.f, -speed, 0.f));
}




int main() {
	Window window("Engine", HEIGHT, WIDTH);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	double start = glfwGetTime();

	float positions[] = {
		800.f, 800.f,
		800.f, 400.f,
		400.f, 400.f,
		400.f, 800.f
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
	Mat4 model(1.f);


	Camera2D camera(window);
	shader.setUniformMatrix4fv("view", camera.getView());
	shader.setUniformMatrix4fv("model", model);
	shader.setUniformMatrix4fv("projection", camera.getProjection());
	vao.bind();
	ibo.bind();
	shader.bind();
	
	Utils::Clock clock;
	Utils::Clock camClock;
	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
		test(model, clock.getTimePassed(), 600.f);
		clock.reset();
		handleMove(window, camera, camClock.getTimePassed());
		camClock.reset();
		shader.setUniformMatrix4fv("model", model);
		shader.setUniformMatrix4fv("view", camera.getView());
		window.update();
	}
	glfwTerminate();
	return EXIT_SUCCESS;
}