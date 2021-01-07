#pragma once
#include "../../../Rendering/Textures/Material.h"
#include <glm\ext\matrix_float4x4.hpp>

struct MeshComponent {

private:
	unsigned int VAO;
	unsigned int VBO;
	Material* m_Material;

	void BuildTangents();
public:
	MeshComponent();

	void SetMaterial(const std::string materialName);
	void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform);
	void DrawEditor();
};