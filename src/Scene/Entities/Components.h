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

	void DrawEditor();
};

struct CubeComponent {
	unsigned int VAO;
	unsigned int VBO;

	// TODO: Make material system.
	float Shininess = 1.0f;
	
	CubeComponent();

    void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform);
	void DrawEditor();
};

struct CameraComponent {
    Camera Camera;

	void DrawEditor();
};


enum LightType {
	Directional, Point, Spot
};

struct LightComponent {
	LightType Type = Directional;
	glm::vec3 Direction;
	glm::vec3 Color;
	float Strength;

	float Attenuation = 0.0f;
	float LinearAttenuation = 0.0f;
	float QuadraticAttenuation = 0.0f;

	LightComponent();

	glm::vec3 GetDirection();

	void Draw(TransformComponent transformComponent);

	void DrawEditor();

	void SetType(LightType type);

};