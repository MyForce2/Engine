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


struct LightingConstants {
	Vec4 ambientColor;
	Vec3 lightPosition;
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
	Vec3 color(136, 206, 250);
	color /= 255;
	glClearColor(color.x, color.y, color.z, 1);
	glClearColor(0, 0, 0, 1);
	std::cout << glGetString(GL_VERSION) << std::endl;

	float xMin = 0.f, xMax = 1.f;
	float yMin = 0.f, yMax = 1.f;

	float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, // top-right
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, // top-left
    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // top-right         
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f, // top-right
     0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // top-left
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // top-right     
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // top-left
    -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f // bottom-left        
	};



	const int amount = 10;
	Math::Mat4* translationBuffer = new Math::Mat4[amount];
	for (int i = 0; i < amount; i++) {
		float v = float(i * 2);
		translationBuffer[i] = Mat4::translation(Vec3(v));
	}

	Vec3 cubeColor(50, 0, 0);
	cubeColor /= 255;

	Vec3 lightPosition(0, 0.25f, -2);
	

	std::string prefix = "Resources/Shaders/";
	Shader shader(prefix + "Vertex.shader", prefix + "Fragment.shader");
	Camera camera = Camera(window, 0.1f, 200.f);
	camera.setPosition(Vec3(-2, 0, -2));
	shader.setUniformMatrix4fv("u_Projection", camera.getProjectionMatrix());
	shader.setUniformMatrix4fv("u_View", camera.getViewMatrix());
	shader.setUniformMatrix4fv("u_TexSlot", 0);
	shader.setUniform3f("u_ViewingPosition", camera.getPosition());
	shader.setUniform3f("u_Color", cubeColor);
	shader.setUniform4f("u_AmbientLight", Vec4(color, 0.2));
	shader.setUniform3f("u_LightPosition", lightPosition);
	Texture texture("Resources/Textures/Texture.png");
	texture.setSlot();
	VertexBuffer vbo(cubeVertices, sizeof(cubeVertices));
	VertexBuffer tr(translationBuffer, sizeof(Mat4) * amount);
	VertexArray vao;
	VBLayout layout;
	layout.addElement(3, GL_FLOAT);
	layout.addElement(3, GL_FLOAT);
	vao.addBuffer(vbo, layout);
	vao.addInstancedMatrixBuffer(tr);
	
	BasicRenderer r;

	

	Utils::Clock clock;
	Font f = Font("arial.ttf", 192U * 2);
	Layer2D layer = Layer2D(800.f, 600.f, "Resources/Shaders/QuadVertex.shader", "Resources/Shaders/QuadFragment.shader", f);
	Label l;
	l.setFontSize(36U);
	l.setStartPosition(Vec2(100, 400));
	l.setText("Hello I am testing this super long text");
	l.setLabelColor(Vec3(100, 0, 0));
	Mat4 model = Mat4::translation(Vec2(-l.getStartPosition()));
	model = Mat4::scale(Vec2(0.5, 0.5)) * model;
	model = Mat4::translation(Vec2(l.getStartPosition())) * model;
	l.setModelMatrix(model);

	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		layer.startFrame();
		r.renderArraysInstanced(vao, shader, 0, 36, amount);
		layer.add(l);
		layer.render();
		camera.update(window, clock.getTimePassed());
		clock.reset();
		shader.setUniform3f("u_ViewingPosition", camera.getPosition());
		shader.setUniformMatrix4fv("u_View", camera.getViewMatrix());
		shader.setUniformMatrix4fv("u_Projection", camera.getProjectionMatrix());
		shader.setUniform3f("u_LightPosition", lightPosition);
		window.update();
	}

	glfwTerminate();
	Utils::Log::closeLog();
	return EXIT_SUCCESS;
}