#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

class Mesh {
private:
	std::vector<Vertex> m_Vertexes;
	std::vector<unsigned int> m_Indices;

	unsigned int m_Vao;
	unsigned int m_Vbo;
	unsigned int m_Ebo;
public:
	Mesh(std::vector<Vertex> vertexes,  std::vector<unsigned int> indices);
	~Mesh();

	void render();
	//void render(Shader& shader);
};

