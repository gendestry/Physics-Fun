#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ResourceManager.h"
#include "Mesh.h"

class Application {
private:
	unsigned int m_Width;
	unsigned int m_Height;
	GLFWwindow* m_Window;

	float m_FOV = 45.0f;
	glm::mat4 m_Projection;

	ResourceManager m_ResManager;

	// temp
	Mesh* cube;
public:
	Application(unsigned int width, unsigned int height, GLFWwindow* window);
	~Application();

	void handleEvents();
	void update(double dt);
	void render(double dt);
};