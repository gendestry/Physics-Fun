#include "Application.h"
#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

Application::Application(unsigned int width, unsigned int height, GLFWwindow* window) 
	: m_Width(width), m_Height(height), m_Window(window) {

	m_Projection = glm::perspective(m_FOV, (float)m_Width / (float)m_Height, 0.01f, 500.0f);

	m_ResManager.addShader("basic", new Shader("shaders/basic-vert.glsl", "shaders/basic-frag.glsl"));
	m_ResManager.getShader("basic")->setMat4("proj", m_Projection);
	m_ResManager.getShader("basic")->setMat4("view", glm::mat4(1.0f));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

Application::~Application() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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

	// imgui begin frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	static glm::vec4 color;
	static float val;
	if (ImGui::Begin("Test window")) {
		if(ImGui::ColorEdit4("ClearColor", &color[0]))
			glClearColor(color.r, color.g, color.b, color.a);
		ImGui::SliderFloat("Test", &val, 0.0f, 1.0f);
	}
	ImGui::End();

	// imgui render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}