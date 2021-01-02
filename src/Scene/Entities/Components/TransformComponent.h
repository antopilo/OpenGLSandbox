#pragma once
#include <glm\ext\matrix_float4x4.hpp>
struct TransformComponent {
	glm::vec3 Translation;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	TransformComponent();
	glm::mat4 GetTransform();

	void DrawEditor();
};