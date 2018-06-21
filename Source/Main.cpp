#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Math\Math.h"
#include "Graphics\Graphics.h"
#include "Utils/Utils.h"




#include <iostream>
#include <chrono>
#include <thread>

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

Vec3* createNormalsBuffer(float* vertices) {
	return nullptr;
}


void handleInput(const Window& window, Camera* camera, float time) {
	float cameraSpeed = 6.f * time;
	Vec3 pos = camera->getPosition();
	Vec3 direction = camera->getViewingDirection();
	if (window.isKeyPressed(GLFW_KEY_X)) {
		cameraSpeed *= 10;
	}
	if (window.isKeyPressed(GLFW_KEY_S)) {
		pos -= direction * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_W)) {
		pos += direction * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_A)) {
		pos -= direction.cross(Vec3(0, 1, 0)).normalized() * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_D)) {
		pos += direction.cross(Vec3(0, 1, 0)).normalized() * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_SPACE)) {
		pos += Vec3(0, 1, 0) * cameraSpeed;
	}
	if (window.isKeyPressed(GLFW_KEY_R)) {
		pos -= Vec3(0, 1, 0) * cameraSpeed;
	}
	camera->setPosition(pos);
}

int main() {
	Utils::Log::getLog()->logInfo("Starting run");
	Window window("Engine", HEIGHT, WIDTH, GL_COLOR_BUFFER_BIT);
	if (glewInit() != GLEW_OK) {
		Utils::Log::getLog()->logError("Failed to init glew, terminating");
		return EXIT_FAILURE;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Vec3 clearColor(0.f / 255.f, 191.f / 255.f, 255.f / 255.f);
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.f);
	std::cout << glGetString(GL_VERSION) << std::endl;

	float start = 0.f;
	float end = 1.f;;

	TextureAtlas atlas("Resources/Textures/DefaultPack2.png", 256, 16);
	const Texture& tex = atlas.getTexture();
	auto uv = atlas.getUVCoordinates(0);

	float xMaxA = uv[0];
	float yMaxA = uv[1];
	float xMinA = uv[2];
	float yMinA = uv[5];

	auto uvTwo = atlas.getUVCoordinates(0);

	float xMax = uvTwo[0];
	float yMax = uvTwo[1];
	float xMin = uvTwo[2];
	float yMin = uvTwo[5];



	float positionsTex[] = {
		-1.f, -1.f, -1.f,  xMinA, yMinA, // Bottom-left
		1.f,  1.f, -1.f,  xMaxA, yMaxA, // top-right
		1.f, -1.f, -1.f,  xMaxA, yMinA, // bottom-right         
		1.f,  1.f, -1.f,  xMaxA, yMaxA, // top-right
		-1.f, -1.f, -1.f,  xMinA, yMinA, // bottom-left
		-1.f,  1.f, -1.f,  xMinA, yMaxA, // top-left
		
		// Front face
		-1.f, -1.f,  1.f,   xMinA, yMinA, // bottom-left
		1.f, -1.f,  1.f,   xMaxA, yMinA,  // bottom-right
		1.f,  1.f,  1.f,   xMaxA, yMaxA,  // top-right
		1.f,  1.f,  1.f,   xMaxA, yMaxA,  // top-right
		-1.f,  1.f,  1.f,   xMinA, yMaxA, // top-left
		-1.f, -1.f,  1.f,   xMinA, yMinA, // bottom-left
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


	float colorBuffer[36 * 3];
	srand(time(nullptr));
	for (int i = 0; i < 36 * 3; i++) {
		float val = float(rand() % 256);
		val /= 256;
		colorBuffer[i] = val;
	}

	int lim = 70;
	int distance = 3;
	int amount;
	if (lim % distance == 0) {
		amount = lim / distance;
	} else {
		amount = lim / distance + lim % distance;
	}

	int objAmount = amount * amount * amount;

	Mat4* translationsBuffer = new Mat4[objAmount];
	int index = 0;
	for (int x = 0; x < lim; x += distance) {
		for (int y = 0; y < lim; y += distance) {
			for (int z = 0; z < lim; z += distance) {
				Vec3 translation(x, y, z);
				Mat4 rotation = Mat4::rotationX(90.f);
				translationsBuffer[index] = Mat4::translation(translation) * rotation;
				index++;
			}
		}
	}

	VertexArray vao;
	VBLayout colorLayout;
	VBLayout verticesLayout;
	colorLayout.addElement(3, GL_FLOAT);
	verticesLayout.addElement(3, GL_FLOAT);
	verticesLayout.addElement(2, GL_FLOAT);
	VertexBuffer colors(colorBuffer, sizeof(colorBuffer));
	VertexBuffer posTex(positionsTex, sizeof(positionsTex));
	VertexBuffer translations(translationsBuffer, objAmount * sizeof(Mat4));
	vao.addBuffer(posTex, verticesLayout);
	vao.addBuffer(colors, colorLayout);
	vao.addMatrixBuffer(translations);
	vao.bind();
	Shader shader("Resources/Shaders/Vertex.shader", "Resources/Shaders/Fragment.shader");
	Mat4 matrix(1.f);
	float w = float(WIDTH);
	float h = float(HEIGHT);
	Camera c(window, 0.1f, 250.f);
	c.setPosition(Vec3(40, 0, 15));
	c.setViewingDirection(Vec3(0, 0, -1.f));
	c.update(window);
	Mat4 model(1.f);
	Texture t("Resources/Textures/grass_side.png");
	t.setSlot();
	shader.setUniformMatrix4fv("view", c.getViewMatrix());
	shader.setUniformMatrix4fv("model", model);
	shader.setUniformMatrix4fv("projection", c.getProjectionMatrix());
	shader.setUniform1i("texSlot", 0);
	shader.setUniform3f("lightColor", clearColor);


	float quadPos[] = {
		1.f, 1.f, 1.f, 1.f,
		-1.f, 1.f, 0.f, 1.f,
		-1.f, -1.f, 0.f, 0.f,
		1.f, -1.f, 1.f, 0.f
	};

	unsigned short quadIndices[] = {
		0, 1, 2, 0, 2, 3
	};

	Shader fboShader("Resources/Shaders/PPVertex.shader", "Resources/Shaders/PPFragment.shader");
	IndexBuffer ibo(quadIndices, 6);
	VertexBuffer fboBuff(quadPos, sizeof(quadPos));
	VBLayout layout;
	layout.addElement(2, GL_FLOAT);
	layout.addElement(2, GL_FLOAT);
	VertexArray quadVao;
	quadVao.addBuffer(fboBuff, layout);
	fboShader.setUniform1i("u_TextureSlot", 0);
	fboShader.setUniform3f("u_ClearColor", clearColor);

	FrameBuffer fbo(w, h);
	fbo.bindRenderBuffer();

	Shader s("Resources/Shaders/QuadVertex.shader", "Resources/Shaders/QuadFragment.shader");

	BasicRenderer renderer;

	vao.bind();
	shader.bind();
	t.setSlot();
	window.setMousePosition(window.getSize() / 2);

	delete[] translationsBuffer;

	Utils::Clock clock;

	Vec2 size = window.getSize();
	
	int max = lim * lim * lim;

	while (!window.isClosed() && window.isKeyReleased(GLFW_KEY_ESCAPE)) {
		handleInput(window, &c, clock.getTimePassed());
		clock.reset();
		c.update(window);
		if (window.getSize() != size) {
			size = window.getSize();
			fbo.setSize(size);
		}
		shader.setUniformMatrix4fv("view", c.getViewMatrix());
		fbo.bind();
		glEnable(GL_DEPTH_TEST);
		FrameBuffer::clearBuffer(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		tex.setSlot();
		renderer.renderArraysInstanced(vao, shader, 0, 36, objAmount);
		fbo.unBind();
		glDisable(GL_DEPTH_TEST);
		fboShader.bind();
		fbo.bindTexture();
		renderer.renderElements(quadVao, fboShader, ibo);

		window.update();
	}
	glfwTerminate();
	Utils::Log::closeLog();
	return EXIT_SUCCESS;
}