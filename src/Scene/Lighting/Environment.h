#pragma once
#include <glm\ext\vector_float4.hpp>
#include <glm\ext\vector_float3.hpp>

class Environment
{
public:
	Environment();

	glm::vec4 m_AmbientColor;
	glm::vec4 GetAmbientColor();
	void SetAmbientColor(glm::vec4 color);
	
	glm::vec4 m_DirectionalLightColor;
	glm::vec4 GetDirectionalLightColor();
	void SetDirectionalLightColor(glm::vec4 color);

	glm::vec3 m_DirectionalLight = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 GetDirectionalLight();
	void SetDirectionalLight(float x, float y, float z);

	float m_DirectionalStrength;
	float GetDirectionalStrength();
	
};
