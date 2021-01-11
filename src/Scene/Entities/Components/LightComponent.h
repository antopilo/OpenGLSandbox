#pragma once
#include <glm\ext\vector_float3.hpp>
#include "TransformComponent.h"
#include "../Rendering/Camera.h"
#include "../../../Rendering/Framebuffer.h"
enum LightType {
	Directional, Point, Spot
};

struct LightComponent {
	LightType Type = Point;
	glm::vec3 Direction;
	glm::vec3 Color;
	float Strength;

	FrameBuffer* m_Framebuffer;

	bool CastShadows = true;
	float Attenuation = 0.0f;
	float LinearAttenuation = 0.0f;
	float QuadraticAttenuation = 0.0f;

	LightComponent();

	glm::mat4 GetProjection();

	glm::mat4 GetLightTransform();

	glm::vec3 GetDirection();

	void BeginDrawShadow();

	void EndDrawShadow();
	void DrawShadow();

	void Draw(TransformComponent transformComponent, Camera* cam);

	void DrawEditor();

	void SetType(LightType type);

};