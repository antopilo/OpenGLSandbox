#pragma once
#include <string>
#include <vector>
#include "../Rendering/Mesh/Mesh.h"

class QuakeMap {
private:
	std::string m_Path;
	std::vector<Mesh> m_Meshes;
public:
	void Load(std::string path);
	void Build();
	void Rebuild();
	void Draw();
};