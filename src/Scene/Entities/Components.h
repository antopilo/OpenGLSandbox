#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <string>
#include "../Rendering/Camera.h"

struct NameComponent {
    std::string Name;
};

struct TransformComponent {
	glm::vec3 Translation;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	TransformComponent();
	glm::mat4 GetTransform();
};

struct CubeComponent {
	unsigned int VAO;
	unsigned int VBO;

	CubeComponent();

    void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform);
};

struct CameraComponent {
    Camera Camera;
};


enum LightType {
	Point, Directional, Spot
};
struct LightComponent {
	LightType Type = Directional;
	glm::vec3 Direction;
	glm::vec3 Color;
	float Strength;

	LightComponent();

	glm::vec3 GetDirection();

	void Draw(TransformComponent transformComponent);
};