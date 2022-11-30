#include "ResourceManager.h"

ResourceManager::~ResourceManager() {
	for (auto& it : m_Shaders) {
		delete it.second;
	}

	for (auto& it : m_Textures) {
		delete it.second;
	}
}

void ResourceManager::addShader(const char* name, Shader* shader) {
	if (m_Shaders.find(name) == m_Shaders.end())
		m_Shaders[name] = shader;
}

void ResourceManager::addTexture(const char* name, Texture* texture) {
	if (m_Textures.find(name) == m_Textures.end())
		m_Textures[name] = texture;
}

Shader* ResourceManager::getShader(const char* name) {
	if (m_Shaders.find(name) != m_Shaders.end())
		return m_Shaders[name];

	return nullptr;
}

Texture* ResourceManager::getTexture(const char* name) {
	if (m_Textures.find(name) != m_Textures.end())
		return m_Textures[name];

	return nullptr;
}