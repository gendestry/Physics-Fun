#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Application.h"

const int WIDTH = 800;
const int HEIGHT = 608;

GLFWwindow* window;
Application* app;

void init() {
	if (!glfwInit())
		std::cerr << "[GLFW] Could not initialize!" << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Bullet physics test", NULL, NULL);

	if (!window) {
		std::cerr << "[GLFW] Window not created!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress)) {
		std::cerr << "[GLAD] Could not initialise!" << std::endl;
		glfwTerminate();
		return;
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// class initialisation
	app = new Application(WIDTH, HEIGHT, window);
}

int main() {
	init();

	while (!glfwWindowShouldClose(window)) {
		app->handleEvents();	// key and mouse input
		app->update();			// updates
		app->render();			// rendering
	}

	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}