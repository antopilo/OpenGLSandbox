#include "TextureManager.h"
#include "../Rendering/Textures/Texture.h"

TextureManager* TextureManager::s_Instance;
std::map<std::string, Texture*> TextureManager::m_Registry;

bool TextureManager::IsTextureLoaded(const std::string path)
{
	return m_Registry.find(path) != m_Registry.end();
}

Texture* TextureManager::GetTexture(const std::string path)
{
	if (!IsTextureLoaded(path))
		m_Registry.emplace(path, new Texture(path));

	return m_Registry.at(path);
}