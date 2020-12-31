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
	void Push();
};
