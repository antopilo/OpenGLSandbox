#pragma once
#include <map>
#include <string>


class Texture;

class TextureManager
{
public:
	static TextureManager* Get() { return s_Instance; }

	TextureManager() { s_Instance = this; }

	Texture* GetTexture(const std::string path);

private:
	static TextureManager* s_Instance;

	static std::map<std::string, Texture*> m_Registry;
	bool IsTextureLoaded(const std::string path);
};