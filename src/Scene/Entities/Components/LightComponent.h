#pragma once
#include <glm\ext\vector_float3.hpp>
#include "../Components.h"

enum LightType {
	Directional, Point, Spot
};

struct LightComponent {
	LightType Type = Point;
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