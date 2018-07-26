#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include <Typo/Typo.h>
#include <vector>
#include "Utils/Utils.h"
#include <Windows.h>
#include "Graphics/Layers/Layer2D.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <unordered_map>

#define BLOCKS true

using namespace Engine;
using namespace Math;
using namespace Graphics;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

static const int WIDTH = 1280;
static const int HEIGHT = 720;
static const float ANGLE_PER_SEC = 120.f;

static const int COLOR_BUFFER_SIZE = 8 * 3;



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




int main() {
	Utils::Log::getLog()->logInfo("Starting run");
	Window window("Engine", HEIGHT, WIDTH, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (glewInit() != GLEW_OK) {
		Utils::Log::getLog()->logError("Failed to init glew, terminating");
		return EXIT_FAILURE;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.5, 0.5, 0, 1);

	std::cout << glGetString(GL_VERSION) << std::endl;

	float xMin = 0.f, xMax = 1.f;
	float yMin = 0.f, yMax = 1.f;


	float positionsTex[] = {
		-1.f, -1.f, -1.f,  xMin, yMin, // Bottom-left
		1.f,  1.f, -1.f,  xMax, yMax, // top-right
		1.f, -1.f, -1.f,  xMax, yMin, // bottom-right         
		1.f,  1.f, -1.f,  xMax, yMax, // top-right
		-1.f, -1.f, -1.f,  xMin, yMin, // bottom-left
		-1.f,  1.f, -1.f,  xMin, yMax, // top-left

		// Front face
		-1.f, -1.f,  1.f,   xMin, yMin, // bottom-left
		1.f, -1.f,  1.f,   xMax, yMin,  // bottom-right
		1.f,  1.f,  1.f,   xMax, yMax,  // top-right
		1.f,  1.f,  1.f,   xMax, yMax,  // top-right
		-1.f,  1.f,  1.f,   xMin, yMax, // top-left
		-1.f, -1.f,  1.f,   xMin, yMin, // bottom-left
		// Left face
		-1.f,  1.f,  1.f,  xMax, yMax, // top-right
		-1.f,  1.f, -1.f,  xMin, yMax, // top-left
		-1.f, -1.f, -1.f,  xMin, yMin, // bottom-left
		-1.f, -1.f, -1.f,  xMin, yMin, // bottom-left
		-1.f, -1.f,  1.f,  xMax, yMin, // bottom-right
		-1.f,  1.f,  1.f,  xMax, yMax, // top-right
		// Right face
		1.f,  1.f,  1.f,  xMin, yMax, // top-left
		1.f, -1.f, -1.f,  xMax, yMin, // bottom-right
		1.f,  1.f, -1.f,  xMax, yMax, // top-right         
		1.f, -1.f, -1.f,  xMax, yMin, // bottom-right
		1.f,  1.f,  1.f,  xMin, yMax, // top-left
		1.f, -1.f,  1.f,  xMin, yMin, // bottom-left     
		// Bottom face
		-1.f, -1.f, -1.f,  xMax, yMax, // top-right
		1.f, -1.f, -1.f,  xMin, yMax, // top-left
		1.f, -1.f,  1.f,  xMin, yMin, // bottom-left
		1.f, -1.f,  1.f,  xMin, yMin, // bottom-left
		-1.f, -1.f,  1.f,  xMax, yMin, // bottom-right
		-1.f, -1.f, -1.f,  xMax, yMax, // top-right
		// Top face
		-1.f,  1.f, -1.f,  xMin, yMax, // top-left
		1.f,  1.f,  1.f,  xMax, yMin, // bottom-right
		1.f,  1.f, -1.f,  xMax, yMax, // top-right     
		1.f,  1.f,  1.f,  xMax, yMin, // bottom-right
		-1.f,  1.f, -1.f,  xMin, yMax, // top-left
		-1.f,  1.f,  1.f,  xMin, yMin  // bottom-left
	};

	const int amount = 10;
	Math::Mat4* translationBuffer = new Math::Mat4[amount];
	for (int i = 0; i < amount; i++) {
		float v = float(i * 2);
		translationBuffer[i] = Mat4::translation(Vec3(v));
	}



	std::string prefix = "Resources/Shaders/";
	Shader shader(prefix + "Vertex.shader", prefix + "Fragment.shader");
	Camera camera = Camera(window, 0.1f, 100.f);
	shader.setUniformMatrix4fv("u_Projection", camera.getProjectionMatrix());
	shader.setUniformMatrix4fv("u_View", camera.getViewMatrix());
	shader.setUniformMatrix4fv("u_TexSlot", 0);
	Texture texture("Resources/Textures/Texture.png");
	texture.setSlot();
	VertexBuffer vbo(positionsTex, sizeof(positionsTex));
	VertexBuffer tr(translationBuffer, sizeof(Mat4) * amount);
	VertexArray vao;
	VBLayout layout;
	layout.addElement(3, GL_FLOAT);
	layout.addElement(2, GL_FLOAT);
	vao.addBuffer(vbo, layout);
	vao.addInstancedMatrixBuffer(tr);
	
	BasicRenderer r;
	//Layer2D l = Layer2D(prefix + "QuadVertex.shader", prefix + "QuadFragment.shader");
	//Label label = Label("Label", 22, Vec2(100, 100), Vec3(100, 100, 0));
	

	Utils::Clock clock;

	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		r.renderArraysInstanced(vao, shader, 0, 36, amount);
		camera.update(window, clock.getTimePassed());
		clock.reset();
		shader.setUniformMatrix4fv("u_View", camera.getViewMatrix());
		shader.setUniformMatrix4fv("u_Projection", camera.getProjectionMatrix());
		window.update();
	}

	glfwTerminate();
	Utils::Log::closeLog();
	return EXIT_SUCCESS;
}