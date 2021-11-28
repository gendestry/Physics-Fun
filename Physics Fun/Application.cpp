#include "Application.h"
#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

Application::Application(unsigned int width, unsigned int height, GLFWwindow* window)
	: m_Width(width), m_Height(height), m_Window(window) {

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		// aspect ratio gre v kurac, add fix;
		glViewport(0, 0, width, height);
	});

	m_Projection = glm::perspective(m_FOV, (float)m_Width / (float)m_Height, 0.01f, 500.0f);

	m_ResManager.addShader("basic", new Shader("shaders/basic-vert.glsl", "shaders/basic-frag.glsl"));
	m_ResManager.getShader("basic")->use();
	m_ResManager.getShader("basic")->setMat4("proj", m_Projection);

	glm::mat4 view(1.f);
	view = glm::translate(view, { 0.f, -110.f, 0.f });
	view = glm::rotate(view, glm::radians(35.f), { 1.f, 0.f , 0.f });
	m_ResManager.getShader("basic")->setMat4("view", view);

	glm::mat4 model(1.0f);
	model = glm::translate(model, {0.f, 0.f, -200.0f});
	model = glm::scale(model, glm::vec3(65.0f));
	m_ResManager.getShader("basic")->setMat4("model", model);

	m_ResManager.getShader("basic")->setVec4("imColor", glm::vec4(1.0f));

	float vertices[] = {
		// back
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		// front
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		// left
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		// right
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		// bottom
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		// top
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
	};

	glGenVertexArrays(1, &tVao);
	glBindVertexArray(tVao);
	
	glGenBuffers(1, &tVbo);
	glBindBuffer(GL_ARRAY_BUFFER, tVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	glBindVertexArray(0);

	// IMGUI SETUP
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

Application::~Application() {
	glDeleteBuffers(1, &tVbo);
	glDeleteVertexArrays(1, &tVao);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Application::handleEvents() {
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);
}

void Application::update(double dt) {

}

void Application::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static glm::vec4 color, imcolor = glm::vec4(1.0f);
	static glm::vec3 position = { 0.0f, 0.0f, -200.0f };
	static glm::vec3 rotation(0.0f);

	glBindVertexArray(tVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// imgui begin frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ImGui::ShowDemoWindow();

	if (ImGui::Begin("Some variables")) {
		if(ImGui::ColorEdit4("Clear Color", &color[0]))
			glClearColor(color.r, color.g, color.b, color.a);
		if (ImGui::ColorEdit4("Square Color", &imcolor[0])) {
			m_ResManager.getShader("basic")->use();
			m_ResManager.getShader("basic")->setVec4("imColor", imcolor);
		}
		if (ImGui::DragFloat3("Position", &position[0]) || ImGui::DragFloat3("Rotation", &rotation[0])) {
			glm::mat4 model(1.0f);
			model = glm::translate(model, position);
			model = glm::rotate(model, glm::radians(rotation.x), { 1.f, 0.f, 0.f });
			model = glm::rotate(model, glm::radians(rotation.y), { 0.f, 1.f, 0.f });
			model = glm::rotate(model, glm::radians(rotation.z), { 0.f, 0.f, 1.f });
			model = glm::scale(model, glm::vec3(65.0f));
			m_ResManager.getShader("basic")->use();
			m_ResManager.getShader("basic")->setMat4("model", model);
		}
	}
	ImGui::End();

	// imgui render
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}