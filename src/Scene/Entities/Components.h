#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include <string>

#include "Components/TransformComponent.h"
#include "Components/LightComponent.h"
#include "Components/CameraComponent.h"

struct NameComponent {
    std::string Name;
};

struct CubeComponent {
	unsigned int VAO;
	unsigned int VBO;

	// TODO: Make material system.
	float Shininess = 1.0f;
	glm::vec3 albedo;
	float metallic;
	float roughness;
	float ao;
	CubeComponent();

    void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform);
	void DrawEditor();
};


