#include "Application.h"
#include <glm/gtc/matrix_transform.hpp>

Application::Application(unsigned int width, unsigned int height, GLFWwindow* window) 
	: m_Width(width), m_Height(height), m_Window(window) {

	m_Projection = glm::perspective(m_FOV, (float)m_Width / (float)m_Height, 0.01f, 500.0f);

	shader = new Shader("shaders/basic-vert.glsl", "shaders/basic-frag.glsl");
	shader->setMat4("proj", m_Projection);
	shader->setMat4("view", glm::mat4(1.0f));
}

Application::~Application() {
	delete shader;
}

void Application::handleEvents() {
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	// if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {}
}

void Application::update() {
	static double tprev = 0;
	double time = glfwGetTime() - tprev;

}

void Application::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}