#pragma once
#include "Shader.h"
#include "Texture.h"
#include <unordered_map>

class ResourceManager {
	std::unordered_map<const char*, Shader*> m_Shaders;
	std::unordered_map<const char*, Texture*> m_Textures;
public:
	ResourceManager() = default;
	~ResourceManager();

	void addShader(const char* name, Shader* shader);
	void addTexture(const char* name, Texture* texture);

	Shader* getShader(const char* name);
	Texture* getTexture(const char* name);
};