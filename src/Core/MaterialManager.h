#pragma once
#include <map>
#include <string>
#include "../Rendering/Textures/Material.h"

class MaterialManager {
private:
	static MaterialManager* s_Instance;

	static std::map<std::string, Material*> m_Materials;

	Material* ParseMaterialFile(const std::string path);
	void SaveMaterialFile(const std::string path, Material* material);
	bool IsMaterialLoaded(const std::string path);
public:
	MaterialManager();
	~MaterialManager();

	void LoadMaterials();

	Material* LoadMaterial(const std::string path);

	static MaterialManager* Get() { return s_Instance; }
};